
#include <array>
#include <tuple>

#include <Windows.h>
#include <ktmw32.h>

#include <wil/com.h>
#include <wil/resource.h>
#include <wil/result.h>

#include "factory.h"
#include "protoss_c.h"

HMODULE module_dll;

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) {
	if (rclsid != __uuidof(Nexus) && rclsid != __uuidof(Probe)) {
		return CLASS_E_CLASSNOTAVAILABLE;
	}
	if (rclsid == __uuidof(Nexus)) {
		static ProtossObjectClassFactory<Nexus, INexus> factory;
		return factory.QueryInterface(riid, ppv);
	} else if (rclsid == __uuidof(Probe)) {
		static ProtossObjectClassFactory<Probe, IProbe> factory;
		return factory.QueryInterface(riid, ppv);
	}
	return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI DllCanUnloadNow() {
	// does not support dynamic unload
	return S_FALSE;
}

std::wstring wstring_from_guid(const GUID& iid) {
	wil::unique_cotaskmem_string s{};
	auto hr = ::StringFromIID(iid, s.put());
	if (SUCCEEDED(hr)) {
		return { s.get() };
	}
	LOG_HR(hr);
	return {};
}

std::array<std::tuple<std::wstring_view, std::wstring, std::wstring>, 2> coclasses{
	std::tuple<std::wstring_view, std::wstring, std::wstring> { L"Protoss Nexus", wstring_from_guid(__uuidof(Nexus)), L"Protoss.Nexus.1" },
	std::tuple<std::wstring_view, std::wstring, std::wstring> { L"Protoss Probe", wstring_from_guid(__uuidof(Probe)), L"Protoss.Probe.1" },
};

STDAPI DllRegisterServer() {
	auto get_dll_path = [](std::wstring& dll_path) {
		wchar_t path[MAX_PATH];
		DWORD len = ::GetModuleFileName(module_dll, path, _countof(path));
		RETURN_LAST_ERROR_IF(len == MAX_PATH && path[len - 1] != '\0');
		dll_path = path;
		return S_OK;
	};

	auto create_reg_subkey_with_value = [](HANDLE transaction, HKEY regkey, std::wstring_view subkey_name, std::wstring_view subkey_value) {
		wil::unique_hkey subkey{};
		RETURN_IF_WIN32_ERROR(::RegCreateKeyTransacted(regkey, subkey_name.data(), 0, nullptr, REG_OPTION_NON_VOLATILE,
			KEY_WRITE, nullptr, subkey.put(), nullptr, transaction, nullptr));
		RETURN_IF_WIN32_ERROR(::RegSetValueEx(subkey.get(), nullptr, 0, REG_SZ,
			reinterpret_cast<const BYTE*>(subkey_value.data()), static_cast<DWORD>((subkey_value.size() + 1) * sizeof(wchar_t))));

		return S_OK;
	};

	wil::unique_handle transaction{ ::CreateTransaction(nullptr, nullptr, TRANSACTION_DO_NOT_PROMOTE, 0, 0, INFINITE, nullptr) };
	RETURN_LAST_ERROR_IF(!transaction.is_valid());

	std::wstring dll_path{};
	RETURN_IF_FAILED(get_dll_path(dll_path));

	for (const auto& coclass : coclasses) {
		auto name{ std::get<0>(coclass) };
		auto clsid{ std::get<1>(coclass) };
		auto progId{ std::get<2>(coclass) };

		wil::unique_hkey regkey{};
		// CLSID
		RETURN_IF_WIN32_ERROR(::RegCreateKeyTransacted(HKEY_CLASSES_ROOT, (L"CLSID\\" + clsid).c_str(),
			0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr, regkey.put(), nullptr, transaction.get(), nullptr));
		RETURN_IF_WIN32_ERROR(::RegSetValueEx(regkey.get(), L"", 0, REG_SZ,
			reinterpret_cast<const BYTE*>(name.data()), static_cast<DWORD>((name.size() + 1) * sizeof(wchar_t))));

		RETURN_IF_FAILED(create_reg_subkey_with_value(transaction.get(), regkey.get(), L"InprocServer32", dll_path));
		RETURN_IF_FAILED(create_reg_subkey_with_value(transaction.get(), regkey.get(), L"ProgID", dll_path));

		// ProgID
		RETURN_IF_WIN32_ERROR(::RegCreateKeyTransacted(HKEY_CLASSES_ROOT, progId.c_str(),
			0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr, regkey.put(), nullptr, transaction.get(), nullptr));
		RETURN_IF_WIN32_ERROR(::RegSetValueEx(regkey.get(), L"", 0, REG_SZ,
			reinterpret_cast<const BYTE*>(name.data()), static_cast<DWORD>((name.size() + 1) * sizeof(wchar_t))));

		RETURN_IF_FAILED(create_reg_subkey_with_value(transaction.get(), regkey.get(), L"CLSID", clsid));
	}

	RETURN_IF_WIN32_BOOL_FALSE(::CommitTransaction(transaction.get()));

	return S_OK;
}

STDAPI DllUnregisterServer() {
	wil::unique_handle transaction{ ::CreateTransaction(nullptr, nullptr, TRANSACTION_DO_NOT_PROMOTE, 0, 0, INFINITE, nullptr) };
	RETURN_LAST_ERROR_IF(!transaction.is_valid());

	for (const auto& coclass : coclasses) {
		auto clsid{ std::get<1>(coclass) };
		auto progid{ std::get<2>(coclass) };

		wil::unique_hkey regkey{};
		// CLSID
		RETURN_IF_WIN32_ERROR(::RegOpenKeyTransacted(HKEY_CLASSES_ROOT, (L"CLSID\\" + clsid).c_str(), 0,
			DELETE | KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_SET_VALUE,
			regkey.put(), transaction.get(), nullptr));
		RETURN_IF_WIN32_ERROR(::RegDeleteTree(regkey.get(), nullptr));
		RETURN_IF_WIN32_ERROR(::RegDeleteKeyTransacted(HKEY_CLASSES_ROOT, (L"CLSID\\" + clsid).c_str(), 0, 0, transaction.get(), nullptr));

		// ProgID
		RETURN_IF_WIN32_ERROR(::RegOpenKeyTransacted(HKEY_CLASSES_ROOT, progid.c_str(), 0,
			DELETE | KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_SET_VALUE,
			regkey.put(), transaction.get(), nullptr));
		RETURN_IF_WIN32_ERROR(::RegDeleteTree(regkey.get(), nullptr));
		RETURN_IF_WIN32_ERROR(::RegDeleteKeyTransacted(HKEY_CLASSES_ROOT, progid.c_str(), 0, 0, transaction.get(), nullptr));
	}

	RETURN_IF_WIN32_BOOL_FALSE(::CommitTransaction(transaction.get()));

	return S_OK;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)  {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		module_dll = hModule;
		::DisableThreadLibraryCalls(hModule);
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

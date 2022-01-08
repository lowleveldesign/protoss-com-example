#include <iostream>
#include <iomanip>
#include <string>

#include "protoss_c.h"

std::ostream& operator<<(std::ostream& os, const GUID& guid) {
	const auto prevflags = os.flags();
	os.setf(std::ios_base::hex, std::ios_base::basefield);
	os << std::setfill('0') << std::setw(8) << guid.Data1
		<< "-" << std::setw(4) << guid.Data2
		<< "-" << std::setw(4) << guid.Data3 << "-";

	for (int i = 0; i < 8; i++) {
		if (i == 2) {
			os << "-";
		}
		os << std::setw(2) << static_cast<int>(guid.Data4[i]);
	}
	os.setf(prevflags);
	return os;
}


ULONG __stdcall Nexus::AddRef() {
	ref_count += 1;
	std::cout << "Component: Nexus::AddRef() ref_count = " << ref_count << std::endl;
	return ref_count;
}

ULONG __stdcall Nexus::Release() {
	ref_count -= 1;
	std::cout << "Component: Nexus::Release() ref_count = " << ref_count << std::endl;
	if (ref_count > 0) {
		return ref_count;
	}
	delete this;
	return 0;
}

HRESULT __stdcall Nexus::QueryInterface(REFIID riid, void** ppv) {
	std::cout << "Component: Nexus::QueryInterface: " << riid << std::endl;

	if (riid == IID_IUnknown || riid == __uuidof(INexus)) {
		*ppv = static_cast<INexus*>(this);
	} else if (riid == __uuidof(IGameObject)) {
		*ppv = static_cast<IGameObject*>(this);
	} else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}

HRESULT __stdcall Nexus::CreateUnit(BSTR unit_name, IUnknown** ppUnk) {
	if (std::wstring_view(unit_name) == L"Probe") {
		IProbe* probe = new Probe();
		*ppUnk = probe;

		return S_OK;
	}
	return E_INVALIDARG;
}

ULONG __stdcall Probe::AddRef() {
	ref_count += 1;
	std::cout << "Component: Probe::AddRef() ref_count = " << ref_count << std::endl;
	return ref_count;
}

ULONG __stdcall Probe::Release() {
	ref_count -= 1;
	std::cout << "Component: Probe::Release() ref_count = " << ref_count << std::endl;
	if (ref_count > 0) {
		return ref_count;
	}
	delete this;
	return 0;
}

HRESULT __stdcall Probe::QueryInterface(REFIID riid, void** ppv) {
	std::cout << "Component: Nexus::QueryInterface: " << riid << std::endl;

	if (riid == IID_IUnknown || riid == __uuidof(IProbe)) {
		*ppv = static_cast<IProbe*>(this);
	} else if (riid == __uuidof(IGameObject)) {
		*ppv = static_cast<IGameObject*>(this);
	} else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}

HRESULT __stdcall Probe::ConstructBuilding(BSTR building_name, IUnknown** ppUnk) {
	if (std::wstring_view(building_name) == L"Nexus") {
		INexus* nexus = new Nexus();
		*ppUnk = nexus;

		return S_OK;
	}
	return E_NOINTERFACE;
}


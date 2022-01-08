#pragma once

#include <Windows.h>
#include <wil/com.h>

template<typename T, typename IT>
class ProtossObjectClassFactory : public IClassFactory
{
public:
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv) {
		if (ppv == nullptr) {
			return E_POINTER;
		}

		if (riid == __uuidof(IUnknown) || riid == __uuidof(IClassFactory)) {
			*ppv = static_cast<IClassFactory*>(this);
			return S_OK;
		}

		return E_NOINTERFACE;
	}

	ULONG __stdcall AddRef(void) { return 1; }

	ULONG __stdcall Release(void) { return 1; }

	HRESULT __stdcall CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv) {
		if (pUnkOuter) {
			return CLASS_E_NOAGGREGATION;
		}

		try {
			wil::com_ptr_t<IUnknown> unknown{};
			// attach does not call AddRef (we set ref_count to 1 in COM Objects)
			unknown.attach(static_cast<IT*>(new T()));
			return unknown->QueryInterface(riid, ppv);
		} catch (const std::bad_alloc&) {
			return E_OUTOFMEMORY;
		}

		return S_OK;
	}

	HRESULT __stdcall LockServer(BOOL fLock) {
		UNREFERENCED_PARAMETER(fLock);
		return E_NOTIMPL;
	}
};


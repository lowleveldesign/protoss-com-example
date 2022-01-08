#pragma once

#include <iostream>
#include "..\protoss.h"

class Nexus final : public INexus, public IGameObject
{
	ULONG ref_count;

public:
	Nexus() : ref_count{ 1 } {}
	~Nexus() {
		std::cout << "Component: Nexus::~Nexus()" << std::endl;
	}

	// IUnknown
	virtual ULONG __stdcall AddRef() override;
	virtual ULONG __stdcall Release() override;
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv) override;

	// INexus
	virtual HRESULT __stdcall CreateUnit(BSTR unit_name, IUnknown** ppUnk) override;

	// Inherited via IGameUnit
	virtual HRESULT __stdcall get_Name(BSTR* name) override {
		*name = ::SysAllocString(L"Nexus");
		if (*name == nullptr) {
			return E_OUTOFMEMORY;
		}
		return S_OK;
	}

	virtual HRESULT __stdcall get_Minerals(LONG* minerals) override {
		*minerals = 400;
		return S_OK;
	}

	virtual HRESULT __stdcall get_BuildTime(LONG* buildtime) override {
		*buildtime = 120;
		return S_OK;
	}
};

class Probe final : public IProbe, public IGameObject
{
	ULONG ref_count;

public:
	Probe() : ref_count{ 1 } {}
	~Probe() {
		std::cout << "Component: Probe::~Probe()" << std::endl;
	}

	// IUnknown
	virtual ULONG __stdcall AddRef() override;
	virtual ULONG __stdcall Release() override;
	virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv) override;

	// IProbe
	virtual HRESULT STDMETHODCALLTYPE ConstructBuilding(BSTR building_name, IUnknown** ppUnk) override;

	// IGameUnit
	virtual HRESULT __stdcall get_Name(BSTR* name) override {
		*name = ::SysAllocString(L"Probe");
		if (*name == nullptr) {
			return E_OUTOFMEMORY;
		}
		return S_OK;
	}

	virtual HRESULT __stdcall get_Minerals(LONG* minerals) override {
		*minerals = 50;
		return S_OK;
	}

	virtual HRESULT __stdcall get_BuildTime(LONG* buildtime) override {
		*buildtime = 12;
		return S_OK;
	}
};

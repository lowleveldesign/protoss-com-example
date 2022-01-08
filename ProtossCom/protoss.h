#pragma once

#include <iostream>
#include <combaseapi.h>

struct __declspec(uuid("59644217-3e52-4202-ba49-f473590cc61a")) IGameObject : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE get_Name(BSTR* name) = 0;

	virtual HRESULT STDMETHODCALLTYPE get_Minerals(LONG* minerals) = 0;

	virtual HRESULT STDMETHODCALLTYPE get_BuildTime(LONG* buildtime) = 0;
};

struct __declspec(uuid("C5F45CBC-4439-418C-A9F9-05AC67525E43")) INexus : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE CreateUnit(BSTR unit_name, IUnknown** ppUnk) = 0;
};


struct __declspec(uuid("246A22D5-CF02-44B2-BF09-AAB95A34E0CF")) IProbe : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE ConstructBuilding(BSTR building_name, IUnknown * *ppUnk) = 0;
};

class __declspec(uuid("F5353C58-CFD9-4204-8D92-D274C7578B53")) Nexus final : public INexus, public IGameObject
{
	ULONG ref_count;

public:
	Nexus() : ref_count{ 1 } {}
	~Nexus() {
		std::cout << "Component: Nexus::~Nexus()" << std::endl;
	}

	// IUnknown
	ULONG __stdcall AddRef() override;
	ULONG __stdcall Release() override;
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv) override;

	// INexus
	HRESULT __stdcall CreateUnit(BSTR unit_name, IUnknown** ppUnk) override;

	// Inherited via IGameUnit
	HRESULT __stdcall get_Name(BSTR* name) override {
		*name = ::SysAllocString(L"Nexus");
		if (*name == nullptr) {
			return E_OUTOFMEMORY;
		}
		return S_OK;
	}

	HRESULT __stdcall get_Minerals(LONG* minerals) override {
		*minerals = 400;
		return S_OK;
	}

	HRESULT __stdcall get_BuildTime(LONG* buildtime) override {
		*buildtime = 120;
		return S_OK;
	}
};

class __declspec(uuid("EFF8970E-C50F-45E0-9284-291CE5A6F771")) Probe final : public IProbe, public IGameObject
{
	ULONG ref_count;

public:
	Probe() : ref_count{ 1 } {}
	~Probe() {
		std::cout << "Component: Probe::~Probe()" << std::endl;
	}

	// IUnknown
	ULONG __stdcall AddRef() override;
	ULONG __stdcall Release() override;
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv) override;

	// IProbe
	HRESULT STDMETHODCALLTYPE ConstructBuilding(BSTR building_name, IUnknown** ppUnk) override;

	// IGameUnit
	HRESULT __stdcall get_Name(BSTR* name) override {
		*name = ::SysAllocString(L"Probe");
		if (*name == nullptr) {
			return E_OUTOFMEMORY;
		}
		return S_OK;
	}

	HRESULT __stdcall get_Minerals(LONG* minerals) override {
		*minerals = 50;
		return S_OK;
	}

	HRESULT __stdcall get_BuildTime(LONG* buildtime) override {
		*buildtime = 12;
		return S_OK;
	}
};

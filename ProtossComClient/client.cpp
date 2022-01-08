#include <iostream>

#include <Windows.h>
#include <wil/com.h>

#import "..\protoss.tlb" raw_interfaces_only

using namespace ProtossLib;

HRESULT show_game_unit_data(IUnknown* unknwn) {
	wil::com_ptr_t<IGameObject> unit{};
	RETURN_IF_FAILED(unknwn->QueryInterface(unit.put()));

	wil::unique_bstr name{};
	RETURN_IF_FAILED(unit->get_Name(name.put()));
	LONG minerals;
	RETURN_IF_FAILED(unit->get_Minerals(&minerals));
	LONG buildtime;
	RETURN_IF_FAILED(unit->get_BuildTime(&buildtime));

	std::wcout << L"Name: " << name.get() << L", minerals: " << minerals
		<< L", build time: " << buildtime << std::endl;

	return S_OK;
}

void start_from_probe() {
	wil::com_ptr_t<IProbe> probe{};

	THROW_IF_FAILED(::CoCreateInstance(__uuidof(Probe), nullptr, CLSCTX_INPROC_SERVER, __uuidof(IProbe), probe.put_void()));
	THROW_IF_FAILED(show_game_unit_data(probe.get()));

	auto name{ wil::make_bstr(L"Nexus") };
	wil::com_ptr_t<INexus> nexus{};
	THROW_IF_FAILED(probe->ConstructBuilding(name.get(), nexus.put_unknown()));
	THROW_IF_FAILED(show_game_unit_data(nexus.get()));

}

void start_from_nexus() {
	wil::com_ptr_t<INexus> nexus{};

	THROW_IF_FAILED(::CoCreateInstance(__uuidof(Nexus), nullptr, CLSCTX_INPROC_SERVER, __uuidof(INexus), nexus.put_void()));
	THROW_IF_FAILED(show_game_unit_data(nexus.get()));

	auto name{ wil::make_bstr(L"Probe") };
	wil::com_ptr_t<IProbe> probe{};
	THROW_IF_FAILED(nexus->CreateUnit(name.get(), probe.put_unknown()));
	THROW_IF_FAILED(show_game_unit_data(probe.get()));
}

int main(int argc, char* argv[]) {
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	try {
		// a "smart call object" that will execute CoUnitialize in destructor
		auto runtime{ wil::CoInitializeEx(COINIT_APARTMENTTHREADED) };

		start_from_probe();
		start_from_nexus();

		return 0;
	} catch (const wil::ResultException& ex) {
		std::cout << ex.what() << std::endl;
		return 1;
	} catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return 1;
	}
}
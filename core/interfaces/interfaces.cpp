#include "interfaces.h"
#include "i_app_system.h"
#include "../memory/memory.h"


iv_engine_client* interfaces::engine = nullptr;
i_base_client_dll* interfaces::client = nullptr;
i_client_mode* interfaces::client_mode = nullptr;
i_client_state* interfaces::clientstate = nullptr;
i_input* interfaces::input = nullptr;
i_panel* interfaces::panel = nullptr;
i_surface* interfaces::surface = nullptr;
i_weapon_system* interfaces::weapon_system = nullptr;
i_client_entity_list* interfaces::entity_list = nullptr;
c_global_vars* interfaces::global_vars = nullptr;


template <typename T>
static T* get_interface(char* sz_module, char* sz_interface) {
	typedef void* (*o_interface_t)(char*, int);
	o_interface_t original = (o_interface_t)GetProcAddress(GetModuleHandleA(sz_module), "CreateInterface");
	return (T*)original(sz_interface, 0);
}

bool interfaces::initialize()
{
	client = get_interface<i_base_client_dll, interface_type::index>((char*)"client.dll", (char*)"VClient018");
	engine = get_interface<iv_engine_client, interface_type::index>("engine.dll", "VEngineClient014");
	entity_list = get_interface<i_client_entity_list, interface_type::index>("client.dll", "VClientEntityList003");
	panel = get_interface<i_panel, interface_type::index>((char*)"vgui2.dll", (char*)"VGUI_Panel009");
	surface = get_interface<i_surface, interface_type::index>((char*)"vguimatsurface.dll", (char*)"VGUI_Surface031");
	


	client_mode = **reinterpret_cast<i_client_mode***>((*reinterpret_cast<uintptr_t**>(client))[10] + 5);


	weapon_system = *(i_weapon_system**)(memory::pattern_scan("client.dll", "8B 35 ? ? ? ? FF 10 0F B7 C0") + 2);
	clientstate = **(i_client_state***)(memory::pattern_scan("engine.dll", "A1 ? ? ? ? 8B 80 ? ? ? ? C3") + 1);
	input = *(i_input**)(memory::pattern_scan("client.dll", "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10") + 1);
	global_vars = **reinterpret_cast<c_global_vars***>((*reinterpret_cast<uintptr_t**>(client))[0] + 31);


	return true;
}

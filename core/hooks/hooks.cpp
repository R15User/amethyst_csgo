#include "hooks.h"
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include "../render/render.h"

using namespace std;

unsigned int get_virtual(void* class_, unsigned int index) { return (unsigned int)(*(int**)class_)[index]; }

hooks::create_move::fn create_move_original = nullptr;
hooks::paint_traverse::fn paint_traverse_original = nullptr;

bool hooks::initialize()
{
	auto create_move_target = reinterpret_cast<void*>(get_virtual(interfaces::client_mode, 24));
	auto paint_traverse_target = reinterpret_cast<void*>(get_virtual(interfaces::panel, 41));


	if (MH_Initialize() != MH_OK) {
		throw std::runtime_error("failed to initialize MH_Initialize.");
		return false;
	}



	if (MH_CreateHook(create_move_target, &create_move::hook, reinterpret_cast<void**>(&create_move_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize create_move. (outdated index?)");
		return false;
	}


	if (MH_CreateHook(paint_traverse_target, &paint_traverse::hook, reinterpret_cast<void**>(&paint_traverse_original)) != MH_OK) {
		throw std::runtime_error("failed to initialize paint_traverse. (outdated index?)");
		return false;
	}



	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK) {
		throw std::runtime_error("failed to enable hooks.");
		return false;
	}
	


	return true;
}


bool __fastcall hooks::create_move::hook(void* ecx, void* edx, int sample_frametime, c_usercmd* cmd)
{

	create_move_original(sample_frametime, cmd);


	if (!interfaces::engine->is_in_game() || !cmd || !cmd->command_number)
		return create_move_original(sample_frametime, cmd);

	uintptr_t* frame_pointer;
	__asm mov frame_pointer, ebp;
	bool& send_packet = *reinterpret_cast<bool*>(*frame_pointer - 0x1C);


	//do your CM stuff here


	return false;
}

void __stdcall hooks::paint_traverse::hook(unsigned int panel, bool force_repaint, bool allow_force)
{



	if (!strcmp("MatSystemTopPanel", interfaces::panel->get_name(panel)))
	{
		//draw your stuff here
		render_manager::text("amethyst",10,10,render_manager::fonts::main_font,color(255,255,255));

	}


	paint_traverse_original(interfaces::panel, panel, force_repaint, allow_force);
}




void hooks::restore()
{
	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);
}
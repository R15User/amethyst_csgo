#pragma once

#include <windows.h>
#include <cstdint>
#include <string>
#include <stdexcept>


#include "iv_engine_client.h"
#include "i_client_mode.h"
#include "i_client_entity.h"


#include <Psapi.h>
#include "i_panel.h"
#include "i_surface.h"
#include "i_weapon_system.h"
#include "i_client_entity_list.h"
#include "i_client_state.h"
#include "i_input.h"
#include "i_global_vars.h"

namespace interfaces {
	enum class interface_type { index, bruteforce };

	template <typename ret, interface_type type>
	ret* get_interface(std::string module_name, std::string interface_name) {
		using create_interface_fn = void* (*)(const char*, int*);
		create_interface_fn fn = reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandle(module_name.c_str()), "CreateInterface"));

		if (fn) {
			void* result = nullptr;

			switch (type) {
			case interface_type::index:
				result = fn(interface_name.c_str(), nullptr);




				break;
			case interface_type::bruteforce:
				char buf[128];

				for (uint32_t i = 0; i <= 100; i++) {
					memset((void*)buf, 0, sizeof buf);



					result = fn(interface_name.c_str(), nullptr);

					if (result)
						break;
				}

				break;
			}


			if (!result)
				throw std::runtime_error(interface_name.c_str());

			return reinterpret_cast<ret*>(result);
		}

		return reinterpret_cast<ret*>(nullptr);
	}


	extern iv_engine_client* engine;
	extern i_base_client_dll* client;
	extern i_panel* panel;
	extern i_surface* surface;
	extern i_weapon_system* weapon_system;
	extern i_client_entity_list* entity_list;


	extern i_client_mode* client_mode;
	extern i_client_state* clientstate;
	extern i_input* input;
	extern c_global_vars* global_vars;


	bool initialize();
}
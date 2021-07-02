#include <Windows.h>
#include <thread>
#include <chrono>
#include <stdexcept>
#include <iostream>
#include "interfaces/interfaces.h"
#include "hooks/hooks.h"
#include "render/render.h"

DWORD WINAPI initialize(void* instance)
{
	try
	{
		interfaces::initialize();
		render_manager::init();
		hooks::initialize();
	}
	catch (const std::runtime_error& error) {
		MessageBoxA(NULL, error.what(), "could not init!", MB_OK | MB_ICONERROR);
		FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
	}

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
}



BOOL WINAPI release()
{

	return TRUE;
}

BOOL APIENTRY DllMain(void* instance, uintptr_t reason, void* reserved)
{
	DisableThreadLibraryCalls(static_cast<HMODULE>(instance));

	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		if (auto handle = CreateThread(NULL, NULL, initialize, instance, NULL, NULL))
			CloseHandle(handle);
		break;

	case DLL_PROCESS_DETACH:
		release();
		break;
	}

	return true;
}
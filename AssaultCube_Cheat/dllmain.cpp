#pragma once
#include <Windows.h>
#include "Console.h"
#include "Patch.h"
#include "Offsets.hpp"
#include "Functions.h"
#include "GLHook.hpp"
#include "Hook.hpp"
#include "InputHandler.hpp"
#include "Patches.hpp"
#include "Game.hpp"

DWORD __stdcall run(void* pParam) {
	Sleep(500);


	InputHandler::Init();
	InputHandler::MouseHandler::Init();

	owglSwapBuffers = (twglSwapBuffers)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
	owglSwapBuffers = (twglSwapBuffers)TrampHook((int)owglSwapBuffers, (int)wglSwapBuffersHook, 5);

	Pttc = (PrintTextToChat)PrintTextToChatAddy;
	SDL_ShowCursor = (SDL_ShowCursorhook)SDL_ShowCursorAddy;
	SDL_WM_GrabInput = (SDL_WM_GrabInputhook)SDL_WM_GrabInput;

	console->LogStatus("Cheat Loaded\n");
	Pttc((char*)"[Cheat] %s", (char)"AssaultCube Cheat | By Fiereu");
	Pttc((char*)"[Cheat] %s", (char)"Cheat Loaded");
	return 0x0;
}

bool __stdcall  DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		gModule = hModule;
		CreateThread(nullptr, 0, run, nullptr, 0, nullptr);
		DisableThreadLibraryCalls(0);
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
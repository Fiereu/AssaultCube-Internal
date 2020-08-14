#pragma once
#include <Windows.h>
#include "Console.h"
#include "Patch.h"
#include "Offsets.hpp"
#include "Functions.h"
#include "GLHook.hpp"
#include "Hook.hpp"
#include "Settings.hpp"
#include "Player.hpp"
#include "Aimbot.hpp"
#include "InputHandler.hpp"
#include "Patches.hpp"
#include "Game.hpp"
#include "ESP.hpp"

void Cheat() {


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

	
	while (true) {

		if (ESPToggle)
			ESP();
		if (GetKeyState(0x02) & 0x8000)
			Aimbot();
		if (*onlineMode == 0) {
			*health = 999;
			*InClipPrim = 999;
			*InClipSec = 999;
			*MunPrim = 999;
			*MunSec = 999;
		}
		Sleep(1);
	}


	FreeLibraryAndExitThread((HMODULE)gModule, NULL);
}
DWORD __stdcall run(void* pParam) {
	Cheat();
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
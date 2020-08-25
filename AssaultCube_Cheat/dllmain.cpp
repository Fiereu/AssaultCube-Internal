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

	while (Game::GameWindow == NULL)
	{
		Game::GameWindow = FindWindowA(NULL, "AssaultCube");
	}


	//Definiert Golbale Variablen
	Offsets::EntList = reinterpret_cast<DWORD*>(Offsets::EntListAddy);
	MainPlayer = *(playerent**)Offsets::MainPlayerAddy;
	Game::PlayerCount = reinterpret_cast<int*>(Offsets::PlayerCountAddy);
	Game::onlineMode = reinterpret_cast<int*>(Offsets::onlineModeAddy);
	Game::Gamemode = reinterpret_cast<int*>(Offsets::GamemodeAddy);
	Game::ScreenWidth = reinterpret_cast<int*>(Offsets::ScreenWidthAddy);
	Game::ScreenHeight = reinterpret_cast<int*>(Offsets::ScreenHeightAddy);

	//Hook InputHandler
	InputHandler::Init();
	InputHandler::MouseHandler::Init();

	//Hook OpenGL
	owglSwapBuffers = (twglSwapBuffers)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
	owglSwapBuffers = (twglSwapBuffers)TrampHook((int)owglSwapBuffers, (int)wglSwapBuffersHook, 5);

	//Hooks Pttc Functions
	Pttc = (PrintTextToChat)Offsets::PrintTextToChatAddy;

	//Hooks SDL Functions
	SDL_ShowCursor = (SDL_ShowCursorhook)Offsets::SDL_ShowCursorAddy;
	SDL_WM_GrabInput = (SDL_WM_GrabInputhook)SDL_WM_GrabInput;


	//Startup Message
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
		Game::gModule = hModule;
		CreateThread(nullptr, 0, run, nullptr, 0, nullptr);
		DisableThreadLibraryCalls(0);
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
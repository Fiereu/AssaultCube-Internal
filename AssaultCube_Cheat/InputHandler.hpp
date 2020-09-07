#pragma once
#include <Windows.h>
#include <iostream>
#include "Settings.hpp"
#include "Game.hpp"
#include "Offsets.hpp"
#include "Aimbot.hpp"
#include "Hook.hpp"
#include "GLHook.hpp"
#include "Console.h"
#include "Patches.hpp"
#include "Menu.hpp"

namespace  InputHandler
{
	void _keypress(int code, bool isdown, int cooked, int mod) {
		switch (code)
		{
		case UnloadKey:
			console->LogStatus("Cheat Unloading\n");
			Pttc((char*)"[Cheat] %s", (char)"Unloading");
			FreeLibraryAndExitThread((HMODULE)Game::gModule, NULL);
			break;
		case NoRecoilKey:
			Patches::NoRecoil.Toggle();
			NoRecoilToggled = !NoRecoilToggled;
			break;
		case MenuKey:
			Menu::Visible = !Menu::Visible;
			break;
		case AimbotKey:
			Aimbot();
			AimbotOn = true;
			break;
		case FlyKey:
			console->LogStatus("Fly Toggled\n");
			Pttc((char*)"[Cheat] %s", (char)"Fly Toggled");
			FlyToggled = !FlyToggled;
			if (FlyToggled) {
				MainPlayer->State = 5;
			}
			else {
				MainPlayer->State = 0;
			}
			break;
		case NoSlowdownKey:
			if (*Game::onlineMode == 0) {
				NoSlowdownToggled = !NoSlowdownToggled;
			}
			else 
			{
				Pttc((char*)"[Cheat] %s", (char)"Cant use this NoSlowdown in Online");
				NoSlowdownToggled = false;
			}

			break;
		case FastReloadKey:
			FastReloadToggled = !FastReloadToggled;

			break;
		case OfflineRageKey:
			if (*Game::onlineMode == 0) {
				OfflineRageToggled = !OfflineRageToggled;
			}
			else {
				Pttc((char*)"[Cheat] %s", (char)"Cant use this RageMode in Online");
				OfflineRageToggled = false;
			}

			break;
		default:
			std::cout << code << std::endl;
			break;
		}
		if (MouseIsDown && AimbotOn) {
			Aimbot();
		}
		else {
			AimbotOn = false;
		}

	}

	int hooklen = 6;
	DWORD HookAddy = 0x046C37C;
	DWORD jmpBackAddy = 0x046C382;
	DWORD FunctionAddy = (DWORD)&_keypress;
	void __declspec(naked) Gate() {
		__asm {
			nop
			mov eax, [ebp + 0xC]
			mov ecx, [ebp + 0x8]
			push eax
			push ebx
			push ecx
			push edi
			call[FunctionAddy]
			pop edi
			pop ecx
			pop ebx
			pop eax
			jmp[jmpBackAddy]
			nop
		}
	}

	void Init() {
		DWORD GateAddy = (DWORD)Gate;
		Hook((int)HookAddy, GateAddy + 2, hooklen);
	}
	namespace MouseHandler
	{
		
		void HandleMousInput(int code) {
			switch (code)
			{
			case 5:
				MouseIsDown = true;
				break;
			case 6:
				MouseIsDown = false;
				break;
			default:
				break;
			}
		}


		int hooklen = 8;
		DWORD HookAddy = 0x0475D28;
		DWORD jmpBackAddy = 0x0475D30;
		DWORD FunctionAddy = (DWORD)&HandleMousInput;
		void __declspec(naked) Gate() {
			__asm {
				nop
				push eax
				call[FunctionAddy]
				pop eax
				cmp[esp + 0x4C - 0x30], eax
				mov al, byte ptr[esp + 0x4C - 0x28 + 2]
				jmp[jmpBackAddy]
				nop
			}
		}

		void Init() {
			DWORD GateAddy = (DWORD)Gate;
			Hook((int)HookAddy, GateAddy + 3, hooklen);
		}
		
		
	}
}
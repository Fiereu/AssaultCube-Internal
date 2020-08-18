#pragma once
#include <Windows.h>
#include "Graphics.hpp"
#include "ESP.hpp"
#include "Structs.h"
#include "Settings.hpp"
#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_win32.h"
#include "Gamemode.h"
#include "Game.hpp"
#include "Aimbot.hpp"
#include "Offsets.hpp"

typedef BOOL(__stdcall* twglSwapBuffers)(HDC hDc);
twglSwapBuffers owglSwapBuffers;

#pragma region ImGui

Vector2D WindowSize = { 200,200 };

#pragma endregion

namespace Menu {
	bool Visible = false;
	void Init() {
	}
}

BOOL __stdcall wglSwapBuffersHook(HDC hDc) {
	if (ESPToggle)
		ESP();
	if (GetKeyState(0x02) & 0x8000)
		Aimbot();
	if (*onlineMode == 0) {
		MainPlayer->Health = 999;
		MainPlayer->Amor = 999;
		MainPlayer->MunAssaultRifle = 999;
		MainPlayer->MunCarbin = 999;
		MainPlayer->MunPistol = 999;
		MainPlayer->MunShotgun = 999;
		MainPlayer->MunSniper = 999;
		MainPlayer->MunSub = 999;

		MainPlayer->InClipAssaultRifle = 999;
		MainPlayer->InClipCarbin = 999;
		MainPlayer->InClipPistol = 999;
		MainPlayer->InClipShotgun = 999;
		MainPlayer->InClipSniper = 999;
		MainPlayer->InClipSub = 999;
	}
	if (NoSlowdownToggled) {
		if (MainPlayer->StatePistol == 160) {
			MainPlayer->StatePistol = 0;
		}
		if (MainPlayer->StateShotgun == 880) {
			MainPlayer->StateShotgun = 0;
		}
		if (MainPlayer->StateKnife == 500) {
			MainPlayer->StateKnife = 0;
		}
		if (MainPlayer->StateAssaultRifle == 120) {
			MainPlayer->StateAssaultRifle = 0;
		}
		if (MainPlayer->StateSub == 80) {
			MainPlayer->StateSub = 0;
		}
		if (MainPlayer->StateCarbin == 720) {
			MainPlayer->StateCarbin = 0;
		}
		if (MainPlayer->StateSniper == 1500) {
			MainPlayer->StateSniper = 0;
		}
	}
	if (FastReloadToggled) {
		if (MainPlayer->StatePistol == 1400) {
			MainPlayer->StatePistol = 0;
		}
		if (MainPlayer->StateShotgun == 2400) {
			MainPlayer->StateShotgun = 0;
		}
		if (MainPlayer->StateAssaultRifle == 2000) {
			MainPlayer->StateAssaultRifle = 0;
		}
		if (MainPlayer->StateSub == 1650) {
			MainPlayer->StateSub = 0;
		}
		if (MainPlayer->StateCarbin == 1800) {
			MainPlayer->StateCarbin = 0;
		}
		if (MainPlayer->StateSniper == 1950) {
			MainPlayer->StateSniper = 0;
		}
	}
	if (*onlineMode == 0 && OfflineRageToggled) {
		Vector3D Target;
		GetNearestPlayer(&Target);
		MainPlayer->XHead = Target.x;
		MainPlayer->YHead = Target.y;
		MainPlayer->ZHead = Target.z;
	}
	if (*onlineMode != 0 && OfflineRageToggled) {
		Pttc((char*)"[Cheat] %s", (char)"Cant use this RageMode in Offline");
		OfflineRageToggled = false;
	}

	if (!Font::bBuilt || hDc != Font::hdc)
	{
		Font::Build(15);
		Menu::Init();
	}

	SetupOrtho();
	if (ESPToggle) {
		for (int i = 0; i < enemylist.size(); i++) {
			Vector2D posf;
			Vector2D posh;
			GLMatrix* viewMatrix = ReadMatrix();

			Vector3D Head = { enemylist.at(i)->XHead,enemylist.at(i)->YHead,enemylist.at(i)->ZHead };
			Vector3D Foot = { enemylist.at(i)->XFoot,enemylist.at(i)->YFoot,enemylist.at(i)->ZFoot };

			if (WorldToScreen(Foot, &posf, viewMatrix, *ScreenWidth, *ScreenHeight) && WorldToScreen(Head, &posh, viewMatrix, *ScreenWidth, *ScreenHeight)) {
				float height = posf.y - posh.y;
				float width = height / 2;

				float x1 = posh.x - width / 2.0f;
				float y1 = posh.y;

				if (IsTeamGame(*Gamemode)) {
					if (enemylist.at(i)->team == MainPlayer->team) {
						if (enemylist.at(i)->State == 1)
							DrawOutline(x1, y1, width, height, 1, rgb::gray);
						else
							DrawOutline(x1, y1, width, height, 1, rgb::green);
					}
					else {
						if (enemylist.at(i)->State == 1)
							DrawOutline(x1, y1, width, height, 1, rgb::gray);
						else
							DrawOutline(x1, y1, width, height, 1, rgb::red);
					}
				}
				else {
					if (enemylist.at(i)->State == 1)
						DrawOutline(x1, y1, width, height, 1, rgb::gray);
					else
						DrawOutline(x1, y1, width, height, 1, rgb::red);
				}
			}
		}
	}
	DrawCircle(*ScreenWidth / 2, *ScreenHeight / 2, AimbotFOV * 0.7, 100, rgb::black);

	RestoreGL();
	return owglSwapBuffers(hDc);
}
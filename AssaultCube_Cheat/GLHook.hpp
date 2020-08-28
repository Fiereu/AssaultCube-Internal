#pragma once
#include <Windows.h>
#include "Graphics.hpp"
#include "ESP.hpp"
#include "Structs.h"
#include "Settings.hpp"
#include "Gamemode.h"
#include "Game.hpp"
#include "Aimbot.hpp"
#include "Offsets.hpp"
#include "Functions.h"
#include "InputHandler.hpp"

typedef BOOL(__stdcall* twglSwapBuffers)(HDC hDc);
twglSwapBuffers owglSwapBuffers;



BOOL __stdcall wglSwapBuffersHook(HDC hDc) {
	if (ESPToggled)
		ESP();
	if (GetKeyState(0x02) & 0x8000)
		Aimbot();
	if (*Game::onlineMode == 0) {
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
	if (*Game::onlineMode == 0 && OfflineRageToggled) {
		Vector3D Target;
		GetNearestPlayer(&Target);
		MainPlayer->XFoot = Target.x;
		MainPlayer->YFoot = Target.y;
		MainPlayer->ZFoot = Target.z;
	}
	if (*Game::onlineMode != 0 && OfflineRageToggled) {
		Pttc((char*)"[Cheat] %s", (char)"Cant use this RageMode in Online");
		OfflineRageToggled = false;
	}

	if (!Font::bBuilt || hDc != Font::hdc)
	{
		Font::Build(15);
		Menu::Init();
	}

	SetupOrtho();
	if (ESPToggled) {
		for (int i = 0; i < enemylist.size(); i++) {
			Vector2D posf;
			Vector2D posh;
			GLMatrix* viewMatrix = ReadMatrix();

			Vector3D Head = { enemylist.at(i)->XHead,enemylist.at(i)->YHead,enemylist.at(i)->ZHead };
			Vector3D Foot = { enemylist.at(i)->XFoot,enemylist.at(i)->YFoot,enemylist.at(i)->ZFoot };

			if (WorldToScreen(Foot, &posf, viewMatrix, *Game::ScreenWidth, *Game::ScreenHeight) && WorldToScreen(Head, &posh, viewMatrix, *Game::ScreenWidth, *Game::ScreenHeight)) {
				float height = posf.y - posh.y;
				float width = height / 2;

				float x1 = posh.x - width / 2.0f;
				float y1 = posh.y;

				if (Game::IsTeamGame(*Game::Gamemode)) {
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
	if (AimbotFOVToggled) {
		DrawCircle(*Game::ScreenWidth / 2, *Game::ScreenHeight / 2, AimbotFOV * 0.8, 100, rgb::black);
	}

	if (Menu::Visible) {
		SDL_ShowCursor(1);
		ImGui_ImplOpenGL2_NewFrame();	
		ImGui_ImplWin32_NewFrame();
		ImGui::SetNextWindowSize({ 100,100 });
		ImGui::NewFrame();
		if (ImGui::Begin("Fiereu's AC Cheat", &Menu::Visible, ImGuiWindowFlags_NoResize))
		{
			
			if (ImGui::BeginTabBar("##Menus")) {
				if (ImGui::BeginTabItem("Aimbot", &Menu::M1open)) {
					if (ImGui::BeginCombo("Aimbot Mode", Menu::AimbotCI))
					{
						const char* items[] = { "OFF", "Distance Mode", "FOV Mode" };
						for (int n = 0; n < IM_ARRAYSIZE(items); n++)
						{
							bool is_selected = (Menu::AimbotCI == items[n]);
							if (ImGui::Selectable(items[n], is_selected))
							{
								Menu::AimbotCI = items[n];
								AimbotMode = n;
								if (is_selected)
									ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndCombo();
					}
					
					ImGui::SliderFloat("Min Distance", &AimbotMinDis, 0.0f, 300.0f);
					ImGui::SliderFloat("FOV", &AimbotFOV, 0.0f, 900.0f);
					int t;
					ImGui::SliderInt("Smooth", &t, 0, 5);
					AimbotSmooth = (float)t / 10.0f;

					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Visuals", &Menu::M2open)) {
					ImGui::Checkbox("Show FOV", &AimbotFOVToggled);
					
					ImGui::Checkbox("ESP", &ESPToggled);

					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Misc", &Menu::M3open)) {
					ImGui::Checkbox("NoRecoil", &NoRecoilToggled);
					if (Patches::NoRecoil.isToggled() != NoRecoilToggled) {
						Patches::NoRecoil.Toggle();
					}

					ImGui::Checkbox("FastReload", &FastReloadToggled);

					ImGui::Checkbox("NoSlowdown", &NoSlowdownToggled);

					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
		}
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}
	else {
		SDL_ShowCursor(0);
	}

	RestoreGL();
	return owglSwapBuffers(hDc);
}
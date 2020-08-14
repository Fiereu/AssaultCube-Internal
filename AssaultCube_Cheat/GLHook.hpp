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
			
			Vector3D Head = { enemylist.at(i).xHead,enemylist.at(i).yHead,enemylist.at(i).zHead };
			Vector3D Foot = { enemylist.at(i).xFoot,enemylist.at(i).yFoot,enemylist.at(i).zFoot };

			if (WorldToScreen(Foot, &posf, viewMatrix, *Width, *Height) && WorldToScreen(Head, &posh, viewMatrix, *Width, *Height)) {
				float height = posf.y - posh.y;
				float width = height / 2;

				float x1 = posh.x - width / 2.0f;
				float y1 = posh.y;

				int* isDead = reinterpret_cast<int*>(enemylist.at(i).Base + isDeadAddy);

				if(IsTeamGame(*Gamemode)){
					if (enemylist.at(i).team == *team) {
						if(*isDead == 1)
							DrawOutline(x1, y1, width, height, 1, rgb::gray);
						else
							DrawOutline(x1, y1, width, height, 1, rgb::green);
					}
					else {
						if (*isDead == 1)
							DrawOutline(x1, y1, width, height, 1, rgb::gray);
						else
							DrawOutline(x1, y1, width, height, 1, rgb::red);
					}
				}
				else {
					if (*isDead == 1)
						DrawOutline(x1, y1, width, height, 1, rgb::gray);
					else
						DrawOutline(x1, y1, width, height, 1, rgb::red);
				}
				
				
			}
		}
	}
	DrawCircle(*Width / 2, *Height / 2,AimbotFOV*0.7f,  100, rgb::black);
	

	RestoreGL();
	return owglSwapBuffers(hDc);
}



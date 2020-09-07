#include <Windows.h>
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_win32.h"
#include "Imgui/imgui_impl_opengl2.h"
#include "Game.hpp"
#include "Functions.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Menu {
	bool Visible = false;
	float Width = 300;
	float Height = 500;

	static const char* AimbotCI = "OFF";


	ImGuiIO& io = ImGui::GetIO();
	WNDPROC orgWndProc = NULL;

	LRESULT __stdcall hWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void Init() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(Game::GameWindow);
		ImGui_ImplOpenGL2_Init();

		ImGui::StyleColorsDark();
		orgWndProc = (WNDPROC)SetWindowLongPtr(Game::GameWindow, GWLP_WNDPROC, (LONG_PTR)hWndProc);
		ImGui::SetNextWindowSize({ Width,Height }, 0);
	}

	LRESULT __stdcall hWndProc(const HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (Menu::Visible)
		{
			if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			{
				return true;
			}

			ImGuiIO& io = ImGui::GetIO();

			switch (msg)
			{
			case WM_LBUTTONDOWN:
				io.MouseDown[1] = !io.MouseDown[0];
				return 0;
			case WM_RBUTTONDOWN:
				io.MouseDown[1] = !io.MouseDown[1];
				return 0;
			case WM_MBUTTONDOWN:
				io.MouseDown[2] = !io.MouseDown[2];
				return 0;
			case WM_MOUSEWHEEL:
				return 0;
			case WM_MOUSEMOVE:
				io.MousePos.x = (signed short)(lParam);
				io.MousePos.y = (signed short)(lParam >> 16);
				return 0;
			}
		}
		return CallWindowProcA(Menu::orgWndProc, hWnd, msg, wParam, lParam);
	}
	void Destroy()
	{
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
		SetWindowLongPtr(FindWindowA(NULL, "AssaultCube"), GWLP_WNDPROC, (LONG_PTR)orgWndProc);
		SDL_ShowCursor(0);
	}
	
	void RenderAimbotMenu()
	{
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
		ImGui::SliderFloat("Smooth", &AimbotSmooth, 0.0f, 1.0f);
	}
	void RenderVisualsMenu()
	{
		ImGui::Checkbox("ESP", &ESPToggled);
		ImGui::ColorEdit3("Ally Color", Ally);
		ImGui::ColorEdit3("Enemy Color", Enemy);
		ImGui::ColorEdit3("Dead Color", Dead);
		ImGui::ColorEdit3("FOV Color", FOV);
	}
	void RenderMiscMenu()
	{
		ImGui::Checkbox("NoRecoil", &NoRecoilToggled);
		if (Patches::NoRecoil.isToggled() != NoRecoilToggled) {
			Patches::NoRecoil.Toggle();
		}

		ImGui::Checkbox("FastReload", &FastReloadToggled);

		ImGui::Checkbox("NoSlowdown", &NoSlowdownToggled);
		if (NoSlowdownToggled) {
			if (*Game::onlineMode == 0) {
				console->LogStatus("NoSlowdown Toggled\n");
				Pttc((char*)"[Cheat] %s", (char)"NoSlowdown Toggled");
			}
			else
			{
				Pttc((char*)"[Cheat] %s", (char)"Cant use this NoSlowdown in Online");
				NoSlowdownToggled = false;
			}
		}

		ImGui::Checkbox("Offline RageMode", &OfflineRageToggled);
		if (OfflineRageToggled) {
			if (*Game::onlineMode == 0) {
				console->LogStatus("OfflineRage Toggled\n");
				Pttc((char*)"[Cheat] %s", (char)"OfflineRage Toggled");
			}
			else
			{
				Pttc((char*)"[Cheat] %s", (char)"Cant use this OfflineRage in Online");
				OfflineRageToggled = false;
			}
		}
	}
	void RenderMenu()
	{
		if (ImGui::Begin("Fiereu's AC Cheat", &Menu::Visible, ImGuiWindowFlags_NoResize))
		{
			ImGui::SetWindowSize(ImVec2(Menu::Width, Menu::Height));
			if (ImGui::TreeNode("Aimbot")) {

				RenderAimbotMenu();

				ImGui::EndTabItem();
				ImGui::TreePop();
				ImGui::Separator();
			}
			if (ImGui::TreeNode("Visuals")) {
				ImGui::Checkbox("Show FOV", &AimbotFOVToggled);

				RenderVisualsMenu();

				ImGui::TreePop();
				ImGui::Separator();
			}
			if (ImGui::TreeNode("Misc")) {

				RenderMiscMenu();

				ImGui::TreePop();
				ImGui::Separator();
			}

		}
	}
	void render() {
		SDL_ShowCursor(1);

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();
		
		RenderMenu();

		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}
}


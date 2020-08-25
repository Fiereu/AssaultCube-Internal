#include <Windows.h>
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_win32.h"
#include "Imgui/imgui_impl_opengl2.h"
#include "Game.hpp"
#include "Functions.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Menu {
	bool Visible = false;
	float Width = 0;
	float Height = 0;

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
	
}

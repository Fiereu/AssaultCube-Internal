#pragma once
#include <Windows.h>
#include "Player.hpp"
namespace Offsets
{
	extern DWORD ModuleBaseAddy;
	extern DWORD RecoilAddy;
	extern DWORD MainPlayerAddy;
	extern DWORD onlineModeAddy;
	extern DWORD EntListAddy;
	extern DWORD PlayerCountAddy;
	extern DWORD PrintTextToChatAddy;
	extern DWORD keypressAddy;
	extern DWORD GamemodeAddy;
	extern DWORD ViewMatrixAddy;
	extern DWORD ScreenWidthAddy;
	extern DWORD ScreenHeightAddy;
	extern DWORD SDL_ShowCursorAddy;
	extern DWORD* EntList;
}
namespace Game {
	extern int* PlayerCount;
	extern int* onlineMode;
	extern int* Gamemode;
	extern int* ScreenWidth;
	extern int* ScreenHeight;
}
extern playerent* MainPlayer;

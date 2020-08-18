#pragma once
#include <Windows.h>
#include "Player.hpp"

DWORD ModuleBaseAddy = (DWORD)GetModuleHandle((LPCWSTR)"ac_client.exe");
DWORD RecoilAddy = 0x463786;
DWORD MainPlayerAddy = 0x50F4F4;//ModuleBaseAddy + 0x10F4F4;
DWORD onlineModeAddy = 0x50F414;
DWORD EntListAddy = 0x50F4F8;//ModuleBaseAddy + 0x10F4F8;
DWORD PlayerCountAddy = 0x50F500;//ModuleBaseAddy + 0x10F500;
DWORD PrintTextToChatAddy = 0x046B060;
DWORD keypressAddy = 0x046C320;
DWORD GamemodeAddy = 0x50F49C;
DWORD ViewMatrixAddy = 0x501AE8; // float Matrix[16]
DWORD ScreenWidthAddy = 0x510C94;
DWORD ScreenHeightAddy = 0x510C98;
DWORD SDL_ShowCursorAddy = 0x49E532;

DWORD* EntList = reinterpret_cast<DWORD*>(EntListAddy);
playerent* MainPlayer = *(playerent**)MainPlayerAddy;
int* PlayerCount = reinterpret_cast<int*>(PlayerCountAddy);
int* onlineMode = reinterpret_cast<int*>(onlineModeAddy);
int* Gamemode = reinterpret_cast<int*>(GamemodeAddy);
int* ScreenWidth = reinterpret_cast<int*>(ScreenWidthAddy);
int* ScreenHeight = reinterpret_cast<int*>(ScreenHeightAddy);

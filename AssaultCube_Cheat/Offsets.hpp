#pragma once
#include <Windows.h>
#ifndef OFFSETS_HPP
#define OFFSETS_HPP

DWORD ModuleBaseAddy = (DWORD)GetModuleHandle((LPCWSTR)"ac_client.exe");
DWORD RecoilAddy = 0x463786;
DWORD MainPlayerAddy = 0x50F4F4;//ModuleBaseAddy + 0x10F4F4;
DWORD onlineModeAddy = 0x50F414;
DWORD EnemyListAddy = 0x50F4F8;//ModuleBaseAddy + 0x10F4F8;
DWORD PlayerCountAddy = 0x50F500;//ModuleBaseAddy + 0x10F500;
DWORD HealthAddy = 0xF8;
DWORD xHeadAddy = 0x4;
DWORD yHeadAddy = 0x8;
DWORD xFootAddy = 0x34;
DWORD yFootAddy = 0x38;
DWORD YawMousAddy = 0x40;
DWORD PitchMousAddy = 0x44;
DWORD zHeadAddy = 0xC;
DWORD zFootAddy = 0x3C;
DWORD teamAddy = 0x32C;
DWORD nameAddy = 0x225;
DWORD stateAddy = 0x338;//5 = FlyMode 0= Alive 
DWORD InClipPrimAddy = 0x14C;
DWORD InClipSecAddy = 0x13C;
DWORD MunPrimAddy = 0x124;
DWORD MunSecAddy = 0x114;
DWORD PlayersAddy = ModuleBaseAddy + 0x18A4;
DWORD onGroundAddy = 0x68;
DWORD PrintTextToChatAddy = 0x046B060;
DWORD keypressAddy = 0x046C320;
DWORD GamemodeAddy = 0x50F49C;
DWORD ViewMatrixAddy = 0x501AE8; // float Matrix[16]
DWORD ScreenWidthAddy = 0x510C94;
DWORD ScreenHeightAddy = 0x510C98;
DWORD isDeadAddy = 0x338;

DWORD SDL_ShowCursorAddy = 0x49E532;


DWORD* EnemyList = reinterpret_cast<DWORD*>(EnemyListAddy);
int* PlayerCount = reinterpret_cast<int*>(PlayerCountAddy);
DWORD* MainPlayerBase = reinterpret_cast<DWORD*>(MainPlayerAddy);
int* onlineMode = reinterpret_cast<int*>(onlineModeAddy);
int* onGround = reinterpret_cast<int*>(*MainPlayerBase + onGroundAddy);
int* health = reinterpret_cast<int*>(*MainPlayerBase + HealthAddy);
int* state = reinterpret_cast<int*>(*MainPlayerBase + stateAddy);
int* InClipPrim = reinterpret_cast<int*>(*MainPlayerBase + InClipPrimAddy);
int* InClipSec = reinterpret_cast<int*>(*MainPlayerBase + InClipSecAddy);
int* MunPrim = reinterpret_cast<int*>(*MainPlayerBase + MunPrimAddy);
int* MunSec = reinterpret_cast<int*>(*MainPlayerBase + MunSecAddy);
float* Pitch = reinterpret_cast<float*>(*MainPlayerBase + PitchMousAddy);
float* Yaw = reinterpret_cast<float*>(*MainPlayerBase + YawMousAddy);
float* xHead = reinterpret_cast<float*>(*MainPlayerBase + xHeadAddy);
float* yHead = reinterpret_cast<float*>(*MainPlayerBase + yHeadAddy);
float* zHead = reinterpret_cast<float*>(*MainPlayerBase + zHeadAddy);
int* team = reinterpret_cast<int*>(*MainPlayerBase + teamAddy);
int* Gamemode = reinterpret_cast<int*>(GamemodeAddy);
int* Width = reinterpret_cast<int*>(ScreenWidthAddy);
int* Height = reinterpret_cast<int*>(ScreenHeightAddy);
#endif
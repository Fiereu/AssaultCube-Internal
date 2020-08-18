#pragma once
#include "SDL.h"
typedef int* (__cdecl* PrintTextToChat)(char* Format, char ArgList);
typedef void* (__cdecl* SDL_ShowCursorhook)(int state);
typedef SDL_GrabMode* (__cdecl* SDL_WM_GrabInputhook)(SDL_GrabMode mode);
inline PrintTextToChat Pttc;
inline SDL_ShowCursorhook SDL_ShowCursor;
inline SDL_WM_GrabInputhook SDL_WM_GrabInput;
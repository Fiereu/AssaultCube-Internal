#include "Offsets.hpp"

DWORD Offsets::ModuleBaseAddy = NULL;
DWORD Offsets::RecoilAddy = 0x463786;
DWORD Offsets::MainPlayerAddy = 0x50F4F4;//ModuleBaseAddy + 0x10F4F4;
DWORD Offsets::onlineModeAddy = 0x50F414;
DWORD Offsets::EntListAddy = 0x50F4F8;//ModuleBaseAddy + 0x10F4F8;
DWORD Offsets::PlayerCountAddy = 0x50F500;//ModuleBaseAddy + 0x10F500;
DWORD Offsets::PrintTextToChatAddy = 0x046B060;
DWORD Offsets::keypressAddy = 0x046C320;
DWORD Offsets::GamemodeAddy = 0x50F49C;
DWORD Offsets::ViewMatrixAddy = 0x501AE8; // float Matrix[16]
DWORD Offsets::ScreenWidthAddy = 0x510C94;
DWORD Offsets::ScreenHeightAddy = 0x510C98;
DWORD Offsets::SDL_ShowCursorAddy = 0x49E532;

DWORD* Offsets::EntList = NULL;
playerent * MainPlayer = NULL;
int* Game::PlayerCount = NULL;
int* Game::onlineMode = NULL;
int* Game::Gamemode = NULL;
int* Game::ScreenWidth = NULL;
int* Game::ScreenHeight = NULL;
#ifndef SETTINGS_HPP
#define SETTINGS_HPP
const int UnloadKey = 0x7f;
const int NoRecoilKey = 0x6a;
const int MenuKey = 0x12f;
const int AimbotKey = 0xfffffffd;
const int BunnyHopKey = 0x20;
const int FlyKey = 0x66;
const int ESPKey = 0x0;
const int NoSlowdownKey = 0x6b;
const int FastReloadKey = 0x6c;
const int OfflineRageKey = 0x6f;

bool NoSlowdownToggled = false;

bool FastReloadToggled = false;

bool OfflineRageToggled = false;

bool FlyToggled = false;

bool NoRecoilToggled = false;

bool AimbotFOVToggled = false;
float AimbotSmooth = 0.1f;
int AimbotMode = 0;
bool AimbotOn = false;
float AimbotFOV = 90.0f;
float AimbotMinDis = 120.0f;

bool ESPToggled = false;

#endif
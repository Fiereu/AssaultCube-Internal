#pragma once
#include <Windows.h>
#include <cstdint>
#include "Structs.h"
#include "Offsets.hpp"


class playerent;
class weapon;
class EntList;
bool IsValidEnt(playerent* ent);
void PlayerToVector(playerent* p, Vector3D* e);

class playerent
{
public:
	uint32_t vTable; //0x0000
	float XHead; //0x0004
	float YHead; //0x0008
	float ZHead; //0x000C
	char pad_0010[12]; //0x0010
	int32_t XSpeed; //0x001C
	int32_t YSpeed; //0x0020
	int32_t Falldistance; //0x0024
	float XVelocity; //0x0028
	float ZVelocity; //0x002C
	float YVelocity; //0x0030
	float XFoot; //0x0034
	float YFoot; //0x0038
	float ZFoot; //0x003C
	float Yaw; //0x0040
	float Pitch; //0x0044
	char pad_0048[4]; //0x0048
	float RecoilMovement; //0x004C
	char pad_0050[4]; //0x0050
	int32_t Falldistance2; //0x0054
	char pad_0058[16]; //0x0058
	int32_t onGround; //0x0068
	char pad_006C[3]; //0x006C
	int32_t MovementFlag; //0x006F
	char pad_0073[13]; //0x0073
	uint8_t WSKey; //0x0080
	uint8_t DAKey; //0x0081
	char pad_0082[10]; //0x0082
	uint8_t A; //0x008C
	uint8_t D; //0x008D
	uint8_t W; //0x008E
	uint8_t S; //0x008F
	char pad_0090[103]; //0x0090
	int32_t Health; //0x00F8
	int32_t Amor; //0x00FC
	char pad_0100[16]; //0x0100
	int32_t MunKnife; //0x0110
	int32_t MunPistol; //0x0114
	int32_t MunCarbin; //0x0118
	int32_t MunShotgun; //0x011C
	int32_t MunSub; //0x0120
	int32_t MunSniper; //0x0124
	int32_t MunAssaultRifle; //0x0128
	char pad_012C[12]; //0x012C
	int32_t InClipKnife; //0x0138
	int32_t InClipPistol; //0x013C
	int32_t InClipCarbin; //0x0140
	int32_t InClipShotgun; //0x0144
	int32_t InClipSub; //0x0148
	int32_t InClipSniper; //0x014C
	int32_t InClipAssaultRifle; //0x0150
	char pad_0154[12]; //0x0154
	int32_t StateKnife; //0x0160
	int32_t StatePistol; //0x0164
	int32_t StateCarbin; //0x0168
	int32_t StateShotgun; //0x016C
	int32_t StateSub; //0x0170
	int32_t StateSniper; //0x0174
	int32_t StateAssaultRifle; //0x0178
	char pad_017C[12]; //0x017C
	int32_t TimesKnifed; //0x0188
	int32_t TimesShootPistol; //0x018C
	int32_t TimesShootCarbin; //0x0190
	int32_t TimesShootShotgun; //0x0194
	int32_t TimesShootSub; //0x0198
	int32_t TimesShootSniper; //0x019C
	int32_t TimesShootAssaultRifle; //0x01A0
	char pad_01A4[128]; //0x01A4
	char Name[16]; //0x0224
	char pad_0234[248]; //0x0234
	int32_t team; //0x032C
	char pad_0330[8]; //0x0330
	int32_t State; //0x0338
	char pad_033C[68]; //0x033C
	void* Weapon; //0x0380
	char pad_0384[304]; //0x0384
	int32_t Scoped; //0x04B4
}; //Size: 0x04B8

class weapon
{
public:
	char pad_0x0000[0x4]; //0x0000
	__int32 ID; //0x0004
	playerent* owner; //0x0008
	uintptr_t* guninfo; //0x000C
	int* ammo2; //0x0010
	int* ammo; //0x0014
	int* gunWait;
	int shots;
	int breload;
};

struct EntList
{
	playerent* ents[31];
};

bool IsValidEnt(playerent* ent) {
	if (ent)
	{
		if (ent->vTable == 0x4E4A98 || ent->vTable == 0x4E4AC0)
		{
			return true;
		}
	}
	return false;
}
void PlayerToVector(playerent* p, Vector3D* e) {
	e->x = p->XHead;
	e->y = p->YHead;
	e->z = p->ZHead;
}
#pragma once
#include <math.h>
#include <Windows.h>
#include <Vector>
#include "Player.hpp"
#include "Structs.h"
#include "Offsets.hpp"
#include "Game.hpp"
#include "ESP.hpp"


inline bool MouseIsDown = false;

void AimAtTarget(MousePos mp) {
	float newyaw = mp.yaw;
	float newpitch = mp.pitch;
	float oldyaw = MainPlayer->Yaw;
	float oldpitch = MainPlayer->Pitch;
	
	newyaw = newyaw - oldyaw;
	newpitch = newpitch - oldpitch;

	if(mp.yaw < 90.0f && oldyaw > 300.0f)
		if(oldyaw + abs(newyaw) * AimbotSmooth > 360.0f)
			MainPlayer->Yaw = oldyaw + abs(newyaw) * AimbotSmooth - 360.0f;
		else
			MainPlayer->Yaw += abs(newyaw) * AimbotSmooth;
	else if (oldyaw < 90.0f && mp.yaw > 300.0f)
		MainPlayer->Yaw -= abs(newyaw) * AimbotSmooth;
	else
		MainPlayer->Yaw += newyaw * AimbotSmooth;
	MainPlayer->Pitch += newpitch * AimbotSmooth;
}
float Get3dDistance(Vector3D to, Vector3D from)
{
	return (float)
		(sqrt(
			((to.x - from.x) * (to.x - from.x)) +
			((to.y - from.y) * (to.y - from.y)) +
			((to.z - from.z) * (to.z - from.z))
		));
}
float Get2dDistance(Vector2D to, Vector2D from)
{
	
	return (float)
		(sqrt(
			((to.x - from.x) * (to.x - from.x)) +
			((to.y - from.y) * (to.y - from.y))
		));
}
bool GetNearestPlayerFOV(Vector3D* p) {
	Vector3D me;
	PlayerToVector(MainPlayer,&me);
	int Nearest = 99999;
	Vector3D pNearest;
	for (int i = 1; i < *Game::PlayerCount; i++) {
		playerent* enemy = *(playerent**)(*Offsets::EntList + 4 * i);
		if (!IsValidEnt(enemy))
			continue;

		if (Game::IsTeamGame(*Game::Gamemode)) {
			if (enemy->team == MainPlayer->team)
				continue;
		}
		if (enemy->State == 1)
			continue;
		Vector3D enemyVec = { enemy->XHead,enemy->YHead,enemy->ZHead };
		Vector2D pos;
		WorldToScreen(enemyVec, &pos, ReadMatrix(), *Game::ScreenWidth, *Game::ScreenHeight);
		float dis = Get2dDistance({ *Game::ScreenWidth/2,*Game::ScreenHeight/2 }, pos);
		float dis2 = Get3dDistance(enemyVec, me);
		if (dis2 > AimbotMinDis)
			continue;
		if (dis > AimbotFOV&&dis!=0)
			continue;
		if (dis < Nearest) {
			Nearest = dis;
			pNearest = enemyVec;
		}
	}
	if (Nearest == 99999)
		return false;
	*p = pNearest;
	return true;
}
bool GetNearestPlayer(Vector3D* p) {
	Vector3D me;
	PlayerToVector(MainPlayer, &me);
	float Nearest = 99999;
	Vector3D pNearest;
	for (int i = 1; i < *Game::PlayerCount; i++) {
		playerent* enemy = *(playerent**)(*Offsets::EntList + 4 * i);
		if (!IsValidEnt(enemy))
			continue;

		if (Game::IsTeamGame(*Game::Gamemode)) {
			if (enemy->team == MainPlayer->team)
				continue;
		}
		if (enemy->State == 1)
			continue;
		Vector3D enemyVec = { enemy->XHead,enemy->YHead,enemy->ZHead };
		float dis = Get3dDistance(enemyVec, me);

		if (dis < Nearest) {
			Nearest = dis;
			pNearest = enemyVec;
		}
	}
	if (Nearest == 99999)
		return false;
	*p = pNearest;
	return true;
}
void CalculateMousePosition(Vector3D enemy, Vector3D me, MousePos*m)
{
	float x, y, z;
	float pitch, yaw;
	bool positivpitch;

	if (me.x >= enemy.x)
	{
		x = me.x - enemy.x;
	}
	else
	{
		x = enemy.x - me.x;
	}
	if (me.y >= enemy.y)
	{
		y = me.y - enemy.y;
	}
	else
	{
		y = enemy.y - me.y;
	}
	if (me.z >= enemy.z)
	{
		z = me.z - enemy.z;
		positivpitch = false;
	}
	else
	{
		z = enemy.z - me.z;
		positivpitch = true;
	}

	float i = (180 / (float)3.1415);
	float distance = (float)sqrt((x * x) + (y * y));
	yaw = (float)atan((x / y));
	if (z == 0)
		z = (float)0.000000000000000000000000000000000000001;
	pitch = (float)atan((z / distance));

	yaw = yaw * i;
	pitch = pitch * i;
	if (!positivpitch)
		pitch = -pitch;
	if (me.y >= enemy.y && me.x >= enemy.x)
	{
		yaw = 360 - yaw;
	}
	else if (me.y >= enemy.y && me.x < enemy.x) {
		yaw = 0 + yaw;
	}
	else if (me.y < enemy.y && me.x >= enemy.x)
	{
		yaw = 180 + yaw;
	}
	else if (me.y < enemy.y && me.x < enemy.x)
	{
		yaw = 180 - yaw;
	}
	float dist = Get3dDistance(me, enemy);
	
	m->pitch = pitch;
	m->yaw = yaw;
	
	
}

void Aimbot() {
		Vector3D Target;
		if (AimbotMode == 1) {
			if (!GetNearestPlayer(&Target))
				return;
		}
		else if(AimbotMode == 2){
			if (!GetNearestPlayerFOV(&Target))
				return;
		}
		else {
			return;
		}
		MousePos mp;
		Vector3D me;
		PlayerToVector(MainPlayer, &me);
		CalculateMousePosition(Target, me, &mp);
		AimAtTarget(mp);
}
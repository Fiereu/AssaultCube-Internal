#pragma once
#include <math.h>
#include <Windows.h>
#include <Vector>
#include "Player.hpp"
#include "Structs.h"
#include "Offsets.hpp"
#include "Game.hpp"
#ifndef AIMBOT_HPP
#define AIMBOT_HPP

inline bool MouseIsDown = false;

void AimAtTarget(MousePos mp) {
	*Yaw = mp.yaw;
	*Pitch = mp.pitch;
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
	GetMeAsVector(&me);
	int Nearest = 99999;
	Vector3D pNearest;
	for (int i = 1; i < *PlayerCount; i++) {

		DWORD* EnemyBase = reinterpret_cast<DWORD*>(*EnemyList + 4 * i);

		float* Health = reinterpret_cast<float*>(*EnemyBase + HealthAddy);
		if (IsTeamGame(*Gamemode)) {
			int* eteam = reinterpret_cast<int*>(*EnemyBase + teamAddy);
			if (*eteam == *team)
				continue;
		}
		
		int* isDead = reinterpret_cast<int*>(*EnemyBase + isDeadAddy);
		if (*isDead == 1)
			continue;
		float* xHead = reinterpret_cast<float*>(*EnemyBase + xHeadAddy);
		float* yHead = reinterpret_cast<float*>(*EnemyBase + yHeadAddy);
		float* zHead = reinterpret_cast<float*>(*EnemyBase + zHeadAddy);
		Vector3D enemy = { *xHead,*yHead,*zHead };
		Vector2D pos;
		WorldToScreen(enemy, &pos, ReadMatrix(), *Width, *Height);
		float dis = Get2dDistance({ *Width/2,*Height/2 }, pos);
		float dis2 = Get3dDistance(enemy, me);
		if (dis2 > AimbotMinDis)
			continue;
		if (dis > AimbotFOV&&dis!=0)
			continue;
		if (dis < Nearest) {
			Nearest = dis;
			pNearest = enemy;
		}
	}
	if (Nearest == 99999)
		return false;
	*p = pNearest;
	return true;
}
bool GetNearestPlayer(Vector3D* p) {
	Vector3D me;
	GetMeAsVector(&me);
	float Nearest = 99999;
	Vector3D pNearest;
	for (int i = 1; i < *PlayerCount; i++) {
		
		DWORD* EnemyBase = reinterpret_cast<DWORD*>(*EnemyList+4*i);

		float* Health = reinterpret_cast<float*>(*EnemyBase + HealthAddy);
		if (IsTeamGame(*Gamemode)) {
			int* eteam = reinterpret_cast<int*>(*EnemyBase + teamAddy);
			if (*eteam == *team)
				continue;
		}
		int* isDead = reinterpret_cast<int*>(*EnemyBase + isDeadAddy);
		if (*isDead == 1)
			continue;
		float* xHead = reinterpret_cast<float*>(*EnemyBase + xHeadAddy);
		float* yHead = reinterpret_cast<float*>(*EnemyBase + yHeadAddy);
		float* zHead = reinterpret_cast<float*>(*EnemyBase + zHeadAddy);
		Vector3D enemy = { *xHead,*yHead,*zHead };
		float dis = Get3dDistance(enemy, me);

		if (dis < Nearest) {
			Nearest = dis;
			pNearest = enemy;
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
	
	m->pitch = pitch + (dist / 10000.0f);
	m->yaw = yaw;
	
	
}

void Aimbot() {
	if (*EnemyList != 0) {
		Vector3D Target;
		if (AimbotMode == 0) {
			if (!GetNearestPlayer(&Target))
				return;
		}else{
			if (!GetNearestPlayerFOV(&Target))
				return;
		}
		
		MousePos mp;
		Vector3D me;
		GetMeAsVector(&me);
		CalculateMousePosition(Target, me, &mp);
		AimAtTarget(mp);
	}
}

#endif
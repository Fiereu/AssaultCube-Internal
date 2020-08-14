#pragma once
#include "Offsets.hpp"
#include <iostream>
#include "Structs.h"

std::vector<Player> enemylist = std::vector<Player>();
bool WorldToScreen(Vector3D pos, Vector2D* screen, GLMatrix* matrix, int windowWidth, int windowHeight)
{
    Vector4D clipCoords;
    clipCoords.x = pos.x * matrix->Matrix[0] + pos.y * matrix->Matrix[4] + pos.z * matrix->Matrix[8] + matrix->Matrix[12];
    clipCoords.y = pos.x * matrix->Matrix[1] + pos.y * matrix->Matrix[5] + pos.z * matrix->Matrix[9] + matrix->Matrix[13];
    clipCoords.z = pos.x * matrix->Matrix[2] + pos.y * matrix->Matrix[6] + pos.z * matrix->Matrix[10] + matrix->Matrix[14];
    clipCoords.w = pos.x * matrix->Matrix[3] + pos.y * matrix->Matrix[7] + pos.z * matrix->Matrix[11] + matrix->Matrix[15];
    if (clipCoords.w < 0.1f)
        return false;

    Vector3D NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;
	screen->x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen->y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true; // On Screen
}

GLMatrix* ReadMatrix() {
	GLMatrix* m = (GLMatrix*)0x501AE8;
	return  m;
}

void ESP() {
    if (*EnemyList != 0) 
    {
        enemylist.clear();
		for (int i = 1; i < *PlayerCount; i++) {

			DWORD* EnemyBase = reinterpret_cast<DWORD*>(*EnemyList + 4 * i);

			float* Health = reinterpret_cast<float*>(*EnemyBase + HealthAddy);
			int* team = reinterpret_cast<int*>(*EnemyBase + teamAddy);
			float* xHead = reinterpret_cast<float*>(*EnemyBase + xHeadAddy);
			float* yHead = reinterpret_cast<float*>(*EnemyBase + yHeadAddy);
			float* zHead = reinterpret_cast<float*>(*EnemyBase + zHeadAddy);
			float* xFoot = reinterpret_cast<float*>(*EnemyBase + xFootAddy);
			float* yFoot = reinterpret_cast<float*>(*EnemyBase + yFootAddy);
			float* zFoot = reinterpret_cast<float*>(*EnemyBase + zFootAddy);
			Player enemy = { *Health,*team, *xHead,*yHead,*zHead,*xFoot,*yFoot,*zFoot };
			enemy.Base = *EnemyBase;
            enemylist.push_back(enemy);
		}
    }
}
#pragma once
#ifndef STRUCT_H
#define STRUCT_H
typedef struct
{
	float x, y, z, w;
}Vector4D;
typedef struct
{
	float Matrix[16];
}GLMatrix;
typedef struct
{
	float x, y, z;
}Vector3D;
typedef struct
{
	int x, y;
}Vector2D;
typedef struct  {
	const char* name;
	int clipAmmo, fullAmmo;
	int Damage;
}Weapon;
typedef struct  {
	int health,team;
	float xHead, yHead, zHead, xFoot,yFoot,zFoot;
	unsigned long Base;
	Weapon currentweapon;
}Player;

typedef struct
{
	int yaw, pitch;
}MousePos;
typedef enum {
	SDL_GRAB_QUERY,
	SDL_GRAB_OFF,
	SDL_GRAB_ON
} SDL_GrabMode;
#endif
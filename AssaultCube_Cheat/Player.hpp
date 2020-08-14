#pragma once
#include "Offsets.hpp"
#include <Windows.h>
#include "Structs.h"

void GetPlayer(int PlayerBase, Player *player){
	player->health = *health;
	player->xHead = *xHead;
	player->yHead = *yHead;
	player->zHead = *zHead;
}
void GetMeAsVector(Vector3D *me) {
	me->x = *xHead;
	me->y = *yHead;
	me->z = *zHead;
}


void PlayerToVector(Player p, Vector3D *e) {
	e->x = p.xHead;
	e->y = p.yHead;
	e->z = p.zHead;
}
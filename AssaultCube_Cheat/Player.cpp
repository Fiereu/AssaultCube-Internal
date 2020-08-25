#include <Windows.h>
#include <cstdint>
#include "Structs.h"
#include "Offsets.hpp"
#include "Player.hpp"




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
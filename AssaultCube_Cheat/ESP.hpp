#pragma once
#include <vector>

inline std::vector<playerent*> enemylist = std::vector<playerent*>();

bool WorldToScreen(Vector3D pos, Vector2D* screen, GLMatrix* matrix, int windowWidth, int windowHeight);

GLMatrix* ReadMatrix();

void ESP();
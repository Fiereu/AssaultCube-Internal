#pragma once
#include <vector>
#include <Windows.h>
#include <iostream>
class Patch
{
public:
	Patch(int Adress, std::vector<int> orgBytes, int size, std::vector<int> patchBytes);
	~Patch(void);
	LONG Toggle();
	bool isToggled();
private:
	int gAdress;
	bool gToggled = false;
	int gSize;
	std::vector<int> gOrgBytes;
	std::vector<int> gPatchBytes;
	;
};


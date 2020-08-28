#include "Patch.h"


Patch::Patch(int Adress, std::vector<int> orgBytes, int size, std::vector<int> patchBytes)
{
	std::cout << "[+] Patch Created for " << std::hex << Adress << std::endl;
	gAdress = Adress;
	gSize = size;
	gOrgBytes = orgBytes;
	gPatchBytes = patchBytes;
}

Patch::~Patch(void)
{
	std::cout << "[+] Patch Destroyed at " << std::hex << gAdress << " TOGGLED = " + gToggled << std::endl;
}

LONG Patch::Toggle()
{
	LONG STATUS = ERROR_SUCCESS;
	DWORD OldProtect;
	VirtualProtect((LPVOID)gAdress, gSize, PAGE_EXECUTE_READWRITE, &OldProtect);
	if (gToggled) {
		for (int i = 0; i < gSize; i++) {
			memset((void*)(gAdress + i), gOrgBytes.at(i), 1);
		}
		gToggled = !gToggled;
	}
	else {
		for (int i = 0; i < gSize; i++) {
			memset((void*)(gAdress + i), gPatchBytes.at(i), 1);
		}
		gToggled = !gToggled;
	}
	VirtualProtect((LPVOID)gAdress, gSize, OldProtect, nullptr);
	return STATUS;
}

bool Patch::isToggled()
{
	return gToggled;
}

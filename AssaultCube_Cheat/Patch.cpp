#include "Patch.h"


Patch::Patch(int Address, std::vector<int> orgBytes, int size, std::vector<int> patchBytes)
{
	std::cout << "[+] Patch Created for " << std::hex << Address << std::endl;
	gAddress = Address;
	gSize = size;
	gOrgBytes = orgBytes;
	gPatchBytes = patchBytes;
}

Patch::~Patch(void)
{
	std::cout << "[+] Patch Destroyed at " << std::hex << gAddress << " TOGGLED = " + gToggled << std::endl;
}

LONG Patch::Toggle()
{
	LONG STATUS = ERROR_SUCCESS;
	DWORD OldProtect;
	VirtualProtect((LPVOID)gAddress, gSize, PAGE_EXECUTE_READWRITE, &OldProtect);
	if (gToggled) {
		for (int i = 0; i < gSize; i++) {
			memset((void*)(gAddress + i), gOrgBytes.at(i), 1);
		}
		gToggled = !gToggled;
	}
	else {
		for (int i = 0; i < gSize; i++) {
			memset((void*)(gAddress + i), gPatchBytes.at(i), 1);
		}
		gToggled = !gToggled;
	}
	VirtualProtect((LPVOID)gAddress, gSize, OldProtect, nullptr);
	return STATUS;
}

bool Patch::isToggled()
{
	return gToggled;
}

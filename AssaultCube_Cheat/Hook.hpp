#pragma once
#include <Windows.h>
int GetBackAddy(int src, int len) {
	return src + len;
}
int Hook(int src, int dst, int len) {
	if (len < 5)
		return -1;
	DWORD oldProt;
	VirtualProtect((void*)src, len, PAGE_EXECUTE_READWRITE, &oldProt);

	memset((void*)src, 0x90, len);

	int relAddy = dst - src - len;

	*(BYTE*)src = 0xE9;
	*(DWORD*)(src + 1) = relAddy;



	VirtualProtect((void*)src, len, oldProt, nullptr);
	return GetBackAddy(src, len);
}
int TrampHook(int src, int dst, int len) {
	if (len < 5)
		return -1;
	int Gate = (int)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy_s((void*)Gate, len, (void*)src, len);
	int GateRelAdyy = src - Gate - 5;
	*(BYTE*)(Gate + len) = 0xE9;
	*(DWORD*)(Gate + len + 1) = GateRelAdyy;
	Hook(src, dst, len);
	return Gate;
}

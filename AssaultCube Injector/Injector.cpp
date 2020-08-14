#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <iostream>
#include <TlHelp32.h>
#include <string>
#include <string.h>
#include <comdef.h>
#include <filesystem>
#include <fstream>


FILE* stream;
const char* TARGET_PROCESS_NAME = "ac_client.exe";
const char* PAYLOAD_NAME = "AssaultCube_Cheat.dll";



void ConsoleSetup();
int GetProcessIdByName(PCSTR name);
int Inject(int pid);

void ConsoleSetup() {
	AllocConsole();
	freopen_s(&stream, "CONOUT$", "w", stdout);
	HWND con = GetConsoleWindow();
	SetConsoleTitleA("Injector x32");
	MoveWindow(con, 20, 20, 450, 200, true);
}
int GetProcessIdByName(PCSTR name)
{
	DWORD pid = -1;

	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			_bstr_t b(entry.szExeFile);

			if (_stricmp(b, name) == 0)
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);

				pid = GetProcessId(hProcess);

				CloseHandle(hProcess);
				return pid;
			}
		}
		CloseHandle(snapshot);
	}

	CloseHandle(snapshot);
	return pid;
}
int Inject(int pid) {
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	if (INVALID_HANDLE_VALUE == hProcess) {
		std::cout << "[-]Can't create Handle!!!" << std::endl;
		CloseHandle(hProcess);
		return -1;
	}
	char PayloadPath[MAX_PATH];
	GetFullPathNameA(PAYLOAD_NAME, MAX_PATH, PayloadPath, NULL);
	
	std::cout << "[+]PayloadPath " << PayloadPath << std::endl;
	LPVOID RemotePayloadspace = VirtualAllocEx(hProcess, NULL, strlen(PayloadPath), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	std::cout << "[+]RemotePayloadspace 0x" << std::hex << RemotePayloadspace << std::endl;

	BOOL success = WriteProcessMemory(hProcess, RemotePayloadspace, (LPVOID)PayloadPath, strlen(PayloadPath), NULL);
	if (!success) {
		std::cout << "[-]Can't write Processmemory!!!" << std::endl;
		CloseHandle(hProcess);
		return-1;
	}

	LPVOID loadLibraryAddress = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
	std::cout << "[+]LoadLibraryA 0x" << std::hex << loadLibraryAddress << std::endl;

	HANDLE remoteThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)loadLibraryAddress, RemotePayloadspace, NULL, NULL);
	
	CloseHandle(remoteThread);

	CloseHandle(hProcess);

	return 0;
}

int main() {
	ConsoleSetup();
	std::cout << "[+]Console created" << std::endl;
	std::cout << "[+]Starting...." << std::endl;
	std::cout << "[+]Searching Process";
	while (true) {
		int pid = GetProcessIdByName(TARGET_PROCESS_NAME);
		if (pid == -1) {
			std::cout << ".";
		}
		else {
			std::cout << std::endl << "[+]Found Process '" << TARGET_PROCESS_NAME << "' with PID " << pid << std::endl;
			Sleep(3000);
			if (Inject(pid) == 0) {
				std::cout << "[+]Success :D" << std::endl;
			}
			goto EXIT;
		}

		Sleep(100);
	}
EXIT:
	Sleep(9000);
	return 0;
}
#pragma once
#include "Console.h"

Console::Console(const char* title, int width, int height, int posx, int posy)
{
#ifdef DEBUG
	this->title = title;
	this->width = width;
	this->height = height;
	AllocConsole();
	freopen_s(&this->stream, "CONOUT$", "w", stdout);
	this->wnd = GetConsoleWindow();
	SetConsoleTitleA(title);
	MoveWindow(this->wnd, posx, posy, width, height, true);
#endif 
}

Console::~Console()
{
#ifdef DEBUG
	fclose(Console::stream);
	FreeConsole();
#endif 
}

void Console::Move(int width, int height, int posx, int posy) {
#ifdef DEBUG
	MoveWindow(this->wnd, posx, posy, width, height, true);
#endif 
}

void Console::LogInfo(const char* msg)
{
#ifdef DEBUG
	std::cout << "[*] " << msg;
#endif 
}

void Console::LogError(const char* msg)
{
#ifdef DEBUG
	std::cout << "[-] " << msg;
#endif 
}

void Console::LogStatus(const char* msg)
{
#ifdef DEBUG
	std::cout << "[+] " << msg;
#endif 
}

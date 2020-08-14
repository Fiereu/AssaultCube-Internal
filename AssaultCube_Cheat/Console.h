#pragma once
#include <Windows.h>
#include <iostream>
#ifndef CONSOLE_H
#define CONSOLE_H
//#define DEBUG //Remove in Release


class Console
{
public:
	Console(const char* title, int width, int height, int posx, int posy);
	~Console();
	void Move(int width, int height, int posx, int posy);
	void LogInfo(const char* msg);
	void LogError(const char* msg);
	void LogStatus(const char* msg);
	
private:
	const char* title;
	int height, width;
	FILE* stream;
	HWND wnd;
};
inline Console* console = new Console("Debug Console", 600, 500, 20, 20);
#endif
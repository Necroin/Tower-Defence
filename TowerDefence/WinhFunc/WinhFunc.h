#pragma once
#ifndef _WINHFUNC_H_
#define _WINHFUNC_H_
#include <Windows.h>

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);

void gotoxy(HANDLE hConsole, int x, int y);
void gotoxy(int x, int y);

COORD GetCursorWindowPosition();
#endif
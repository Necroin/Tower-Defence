#include "WinhFunc.h"

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

void gotoxy(HANDLE hConsole, int x, int y)
{
	COORD coordinates = { x,y };
	SetConsoleCursorPosition(hConsole, coordinates);
}

void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(hConsole, x, y);
}

COORD GetCursorWindowPosition()
{
	POINT pt;
	GetCursorPos(&pt);
	HWND hwnd = GetConsoleWindow();

	RECT rc;
	GetClientRect(hwnd, &rc);
	ScreenToClient(hwnd, &pt);

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO inf;
	GetConsoleScreenBufferInfo(hout, &inf);

	COORD coord = { 0, 0 };
	coord.X = MulDiv(pt.x, inf.srWindow.Right, rc.right);
	coord.Y = MulDiv(pt.y, inf.srWindow.Bottom, rc.bottom);
	return coord;
}
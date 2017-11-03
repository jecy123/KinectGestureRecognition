#pragma once
#include <Windows.h>

static const int cDepthWidth = 512;
static const int cDepthHeight = 424;
static const float cThreshold = 40;
static const float threshold = cThreshold / 1000.0;

template<class Interface>
inline void SafeRealease(Interface * & pInterfaceToRelease)
{
	if (pInterfaceToRelease != nullptr)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = nullptr;
	}
};

inline void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, coord);
}


#pragma once
#include <Windows.h>
#include <iostream>
#include <opencv2\opencv.hpp>
#include <Kinect.h>
#include <conio.h>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <chrono>

using namespace cv;
using namespace std;

static const int cDepthWidth = 512;
static const int cDepthHeight = 424;
static const float cThreshold = 40;
static const float depthThreshold = cThreshold / 1000.0;


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

inline ULONG getTickCounts()
{
	return GetTickCount();
}

inline void setCursor(int x, int y, float vx = 0.0, float vy = 0.0)
{

	SetCursorPos(x * 5, y * 5);
}




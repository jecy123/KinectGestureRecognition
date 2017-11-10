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

inline string getCurrentSystemTime()
{
	auto tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	char date[60] = { 0 };
	sprintf(date, 
		"%d-%02d-%02d      %02d:%02d:%02d", 
		(int)ptm->tm_year + 1900, 
		(int)ptm->tm_mon + 1, 
		(int)ptm->tm_mday,
		(int)ptm->tm_hour, 
		(int)ptm->tm_min, 
		(int)ptm->tm_sec);
	return string(date);
}



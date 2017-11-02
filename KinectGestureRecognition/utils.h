#pragma once


static const int cDepthWidth = 512;
static const int cDepthHeight = 424;
static const int cThreshold = 50;
static const int threshold = cThreshold / 1000.0;

template<class Interface>
inline void SafeRealease(Interface * & pInterfaceToRelease)
{
	if (pInterfaceToRelease != nullptr)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = nullptr;
	}
};


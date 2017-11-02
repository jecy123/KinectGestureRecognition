#pragma once


static const int cDepthWidth = 512;
static const int cDepthHeight = 424;
static const float cThreshold = 50;
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


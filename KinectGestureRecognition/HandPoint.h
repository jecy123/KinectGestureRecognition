#pragma once
#include <Kinect.h>
#include "dllapi.h"

class DLL_API HandPoint
{
public:
	HandPoint(int x, int y, float z);
	HandPoint(int x, int y, float z, float dis);
	HandPoint();
	~HandPoint();
	
	void setFingerPoint(bool isFingerPoint);
	bool isFingerPoint();

	static float disBtw2Points3d(int x1, int y1, float z1, int x2, int y2, float z2);
	static float disBtw2Points3d(HandPoint & p1, HandPoint & p2);
	static float disBtw2Points(HandPoint & p1, HandPoint & p2);
	static float disBtw2Points(int x1, int y1, int x2, int y2);
	
	static HandPoint & getHandPoint(ICoordinateMapper * mapper, CameraSpacePoint jointPoint);
	
	//三个点构成的两个向量的叉乘(p0p1 × p0p2)
	static int crossProduct(HandPoint & p0, HandPoint & p1, HandPoint & p2);
	//三个点构成的两个二维向量的点乘(p0p1 · p0p2 )
	
	static int dotProduct(HandPoint & p0, HandPoint & p1, HandPoint & p2);
	//三个点构成的两个三维向量的点乘(p0p1 · p0p2 )
	static float dotProduct3d(HandPoint & p0, HandPoint & p1, HandPoint & p2);

	//三个点构成的两个二维向量的夹角cos值：cos< p0p1 , p0p2>
	static float cosin(HandPoint & p0, HandPoint & p1, HandPoint & p2);
	//三个点构成的两个三维向量的夹角cos值：cos< p0p1 , p0p2>
	static float cosin3d(HandPoint & p0, HandPoint & p1, HandPoint & p2);

	bool m_isFingerPoint;
	float m_cameraZ;
	int m_depthX, m_depthY;
	float m_disFromCenter;

 
};


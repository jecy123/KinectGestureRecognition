#pragma once
#include <Kinect.h>

class HandPoint
{
public:
	HandPoint(int x, int y, float z);
	HandPoint();
	~HandPoint();
	void setFingerPoint(bool isFingerPoint);
	bool isFingerPoint();
	static float disBtw2Points(HandPoint p1, HandPoint p2);
	static HandPoint & getHandPoint(ICoordinateMapper * mapper, CameraSpacePoint jointPoint);

	bool m_isFingerPoint;
	float m_cameraZ;
	int m_depthX, m_depthY;
};


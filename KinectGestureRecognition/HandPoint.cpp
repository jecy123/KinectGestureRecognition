#include "HandPoint.h"
#include <cmath>

HandPoint::HandPoint()
{
	m_depthX = m_depthY = 0;

	m_cameraZ = 0;
}

HandPoint::HandPoint(int x, int y, float z) :m_depthX(x), m_depthY(y), m_cameraZ(z)
{
}

HandPoint::~HandPoint()
{
}

void HandPoint::setFingerPoint(bool isFingerPoint)
{
	m_isFingerPoint = isFingerPoint;
}

bool HandPoint::isFingerPoint()
{
	return m_isFingerPoint;
}

//静态方法：
//计算两个手掌指尖点之间的距离值
float HandPoint::disBtw2Points(HandPoint p1, HandPoint p2)
{
	float dis2 = (p1.m_depthX - p2.m_depthX) * (p1.m_depthX - p2.m_depthX)
		+ (p1.m_depthY - p2.m_depthY) * (p1.m_depthY - p2.m_depthY);
	float distance = sqrt(dis2);
	return distance;
}

//静态方法：
//通过摄像头坐标映射到深度空间
HandPoint & HandPoint::getHandPoint(ICoordinateMapper * mapper, CameraSpacePoint point)
{
	int depthX, depthY;
	float cameraZ = point.Z;
	DepthSpacePoint dp;
	mapper->MapCameraPointToDepthSpace(point, &dp);
	depthX = dp.X;
	depthY = dp.Y;

	HandPoint handpoint(depthX, depthY, cameraZ);
	return handpoint;
}
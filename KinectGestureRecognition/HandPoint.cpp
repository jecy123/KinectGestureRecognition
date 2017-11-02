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

//��̬������
//������������ָ���֮��ľ���ֵ
float HandPoint::disBtw2Points(HandPoint p1, HandPoint p2)
{
	float dis2 = (p1.m_depthX - p2.m_depthX) * (p1.m_depthX - p2.m_depthX)
		+ (p1.m_depthY - p2.m_depthY) * (p1.m_depthY - p2.m_depthY);
	float distance = sqrt(dis2);
	return distance;
}

//��̬������
//ͨ������ͷ����ӳ�䵽��ȿռ�
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
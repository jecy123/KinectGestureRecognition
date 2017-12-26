#define DLL_IMPLEMENT

#include "HandPoint.h"
#include "utils.h" 

HandPoint::HandPoint()
{
	m_depthX = m_depthY = 0;

	m_cameraZ = 0;
}


HandPoint::HandPoint(int x, int y, float z, float dis) : m_depthX(x), m_depthY(y), m_cameraZ(z), m_disFromCenter(dis)
{
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
//三个点构成的两个向量的叉乘(p0p1 × p0p2)
int HandPoint::crossProduct(HandPoint & p0, HandPoint & p1, HandPoint & p2)
{
	return (p1.m_depthX - p0.m_depthX) * (p2.m_depthY - p0.m_depthY) - (p2.m_depthX - p0.m_depthX) * (p1.m_depthY - p0.m_depthY);
}

//静态方法：
//三个点构成的两个向量的点乘(p0p1 · p0p2 )
int HandPoint::dotProduct(HandPoint & p0, HandPoint & p1, HandPoint & p2)
{
	return (p1.m_depthX - p0.m_depthX) * (p2.m_depthX - p0.m_depthX) + (p1.m_depthY - p0.m_depthY) * (p2.m_depthY - p0.m_depthY);
}


//静态方法：
//三维空间中三个点构成的两个向量的点乘(p0p1 · p0p2 )
float HandPoint::dotProduct3d(HandPoint & p0, HandPoint & p1, HandPoint & p2)
{
	return (p1.m_depthX - p0.m_depthX) * (p2.m_depthX - p0.m_depthX) 
		+ (p1.m_depthY - p0.m_depthY) * (p2.m_depthY - p0.m_depthY) 
		+ (p1.m_cameraZ - p0.m_cameraZ) * (p2.m_cameraZ - p0.m_cameraZ);
}


//静态方法：
//计算三维空间中两个手掌指尖点之间的距离值
float HandPoint::disBtw2Points3d(int x1, int y1, float z1, int x2, int y2, float z2)
{
	float dis2 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);
	float distance = sqrt(dis2);
	return distance;
}

//静态方法：
//计算三维空间中两个手掌指尖点之间的距离值
float HandPoint::disBtw2Points3d(HandPoint & p1, HandPoint & p2)
{
	return disBtw2Points3d(p1.m_depthX, p1.m_depthY, p1.m_cameraZ, p2.m_depthX, p2.m_depthY, p2.m_cameraZ);
}

//静态方法：
//计算两个手掌指尖点之间的距离值
float HandPoint::disBtw2Points(int x1, int y1, int x2, int y2)
{
	float dis2 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	float distance = sqrt(dis2);
	return distance;
}



//静态方法：
//计算两个手掌指尖点之间的距离值
float HandPoint::disBtw2Points(HandPoint & p1, HandPoint &  p2)
{
	return disBtw2Points(p1.m_depthX, p1.m_depthY, p2.m_depthX, p2.m_depthY);
}

//静态方法：
//计算三个手掌指尖点之间的夹角的cosin
float HandPoint::cosin(HandPoint & p0, HandPoint & p1, HandPoint & p2)
{
	float dot = HandPoint::dotProduct(p0, p1, p2);
	float dis10 = HandPoint::disBtw2Points(p0, p1);
	float dis20 = HandPoint::disBtw2Points(p0, p2);
	return dot / (dis10 * dis20);
}

//静态方法：
//三个点构成的两个三维向量的夹角cos值：cos< p0p1 , p0p2>
float HandPoint::cosin3d(HandPoint & p0, HandPoint & p1, HandPoint & p2)
{
	float dot = HandPoint::dotProduct3d(p0, p1, p2);
	float dis10 = HandPoint::disBtw2Points3d(p0, p1);
	float dis20 = HandPoint::disBtw2Points3d(p0, p2);
	return dot / (dis10 * dis20);
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



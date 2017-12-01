#pragma once
#include "utils.h"
#include "HandPoint.h"
#include "dllapi.h"

#define MAX_FINGERCNT 50
#define MAX_IN_FINGER 4

enum DLL_API checkType
{
	TYPE_HAND_AREA,
	TYPE_HAND_OUTLINE
};

enum DLL_API handType
{
	Hand_one_finger,
	Hand_open,
	Hand_close
};

class DLL_API Hand
{
public:
	Hand();
	~Hand();
	void initHandArray();
	void initFingerArray();
	void clearHandOutLineVector();
	void refreshHandData(ICoordinateMapper * mapper, Joint joints[JointType_Count], UINT16 * depthArray);
	void refreshHandData(ICoordinateMapper * mapper, IBody * pBody, UINT16 * depthArray);
//	void checkFingerPoint(ICoordinateMapper * mapper, UINT16 * depthArray);
	void checkFingerPoint();

	//void refreshHandAreaArray();
	HandPoint	HandCenter;
	HandPoint	HandWrist;
	HandPoint	HandTip;
	HandPoint	HandThumb;

	//HandPoint	m_pMax5FingerPoint[MAX_FINGERCNT];
	//HandPoint	m_pMin4FingerPoint[MAX_IN_FINGER];

	double		maxDis;
	HandPoint	m_leftTopHandPoint;
	HandPoint	m_rightBottomHandPoint;

	HandState	m_handState;



	bool		m_pHandAreaArray[cDepthHeight][cDepthWidth];
	bool		m_pHandLineArray[cDepthHeight][cDepthWidth];
	//bool		m_pHandOutLineArray[cDepthHeight][cDepthWidth];
	vector < HandPoint > HandOutline;
	vector < HandPoint > HandFingers;
private:

	bool				m_visited[cDepthHeight][cDepthWidth];
	CameraSpacePoint	m_points[cDepthHeight * cDepthWidth];
	void	initVisited();
	void	calculateHandRect();
	float	getCameraZFromDepthXY(ICoordinateMapper * mapper, int x, int y, UINT16 DepthZ);
	bool	checkIsOutline(int x, int y);
	bool	dealWithOutline(int x, int y);
	UINT16	conventArray(int x, int y, checkType type = TYPE_HAND_AREA);
	void	findNextXY(const int & oldX, const int & oldY, int & newX, int & newY);

	void	getHandArea(ICoordinateMapper * mapper, UINT16 * depthArray);
	void	getHandOutline(ICoordinateMapper * mapper, UINT16 * depthArray);
};


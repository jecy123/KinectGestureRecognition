#pragma once
#include "utils.h"
#include "HandPoint.h"
#include <vector>
using namespace std;

#define MAX_FINGERCNT 5
#define MAX_IN_FINGER 4

enum checkType
{
	TYPE_HAND_AREA,
	TYPE_HAND_OUTLINE
};

class Hand
{
public:
	Hand();
	~Hand();
	void initHandArray();
	void initFingerArray();
	void deInitHandOutLine();
	void refreshHandData(ICoordinateMapper * mapper, CameraSpacePoint pointCenter, CameraSpacePoint pointWrist, UINT16 * depthArray);
	void checkFingerPoint(ICoordinateMapper * mapper, UINT16 * depthArray);

	//void refreshHandAreaArray();
	HandPoint	HandCenter;
	HandPoint	HandWrist;

	HandPoint	m_pMax5FingerPoint[MAX_FINGERCNT];
	HandPoint	m_pMin4FingerPoint[MAX_IN_FINGER];

	double		maxDis;
	HandPoint	m_leftTopHandPoint;
	HandPoint	m_rightBottomHandPoint;



	bool		m_pHandAreaArray[cDepthHeight][cDepthWidth];
	bool		m_pHandLineArray[cDepthHeight][cDepthWidth];
	bool		m_pHandOutLineArray[cDepthHeight][cDepthWidth];
	vector < HandPoint* > HandOutline;
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
};


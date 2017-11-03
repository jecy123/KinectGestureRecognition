#pragma once
#include "utils.h"
#include "HandPoint.h"
#include <vector>
using namespace std;

class Hand
{
public:
	Hand();
	~Hand();
	void initHandArray();

	void refreshHandData(ICoordinateMapper * mapper, CameraSpacePoint point, UINT16 * depthArray);
	//void refreshHandAreaArray();
	HandPoint HandCenter;
	HandPoint FingePoint;

	double maxDis;

	HandPoint m_leftTopHandPoint;
	HandPoint m_rightBottomHandPoint;

	bool m_pHandAreaArray[cDepthHeight][cDepthWidth];
	bool m_pHandLineArray[cDepthHeight][cDepthWidth];


	vector < HandPoint* > HandOutline;
private:

	bool checkIsOutline(int x, int y);
	UINT16 conventArray(int x, int y);
	CameraSpacePoint m_points[cDepthHeight * cDepthWidth];
	void calculateHandRect();
	float getCameraZFromDepthXY(ICoordinateMapper * mapper, int x, int y, UINT16 DepthZ);

};


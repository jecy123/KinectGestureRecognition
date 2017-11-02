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
	void refreshHandCenter(ICoordinateMapper * mapper, CameraSpacePoint point, UINT16 * depthArray);
	HandPoint HandCenter;

	HandPoint m_leftTopHandPoint;
	HandPoint m_rightBottomHandPoint;

	bool m_pHandAreaArray[cDepthHeight][cDepthWidth];
	bool m_pHandLineArray[cDepthHeight][cDepthWidth];

	vector < HandPoint* > HandOutline;
private:
	void calculateXYOffset();
	float getCameraZFromDepthXY(ICoordinateMapper * mapper, int x, int y, UINT16 DepthZ);

	int m_nXOffsetFromCenter;
	int m_nYOffsetFromCenter;

};


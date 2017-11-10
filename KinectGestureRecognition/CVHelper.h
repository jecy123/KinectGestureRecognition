#pragma once
#include "utils.h"
#include "Hand.h"

class CVHelper
{
public:
	CVHelper();
	~CVHelper();
	void draw(UINT16 * depthData, Hand * rightHand);
	void drawPoint(HandPoint point, Scalar color = cvScalar(0, 255,0),int radius = 5);
	void drawLine(HandPoint p1, HandPoint p2, Scalar color = cvScalar(255, 0, 255));
	void show();
	int getKeyPressed();
	void setCursor(int x, int y);
private:
	Mat m_image;
	int m_nPressedKey;
};


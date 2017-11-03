#pragma once
#include <Kinect.h>
#include <opencv2\opencv.hpp>
#include "Hand.h"

using namespace cv;

class CVHelper
{
public:
	CVHelper();
	~CVHelper();
	void draw(UINT16 * depthData, Hand * rightHand);
	void drawPoint(HandPoint point, Scalar color = cvScalar(0, 255,0),int radius = 5);
	void show();
	int getKeyPressed();
	void setCursor(int x, int y);
private:
	Mat m_image;
	int m_nPressedKey;
};


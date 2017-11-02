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
	void show();
	int getKeyPressed();
private:
	Mat m_image;
	int m_nPressedKey;
};


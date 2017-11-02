#include "CVHelper.h"
#include "utils.h"
#include <string>
#include <cstdio>
#include <opencv2\opencv.hpp>
using namespace cv;
using namespace std;

CVHelper::CVHelper()
{
	m_image.create(cDepthHeight, cDepthWidth, CV_8UC3);
	m_image.setTo(0);
}

CVHelper::~CVHelper()
{
}

void CVHelper::draw(UINT16 * depthData, Hand * rightHand)
{
	m_image.setTo(0);
	//if (depthData != nullptr)
	//{

	//	uchar * imgData = (uchar *)m_image.data;
	//	int j = 0;
	//	for (int i = 0; i < cDepthHeight * cDepthWidth; i++)
	//	{
	//		imgData[j++] = depthData[i];
	//		imgData[j++] = depthData[i];
	//		imgData[j++] = depthData[i];
	//	}
	//}

	if (rightHand != nullptr)
	{
		uchar * imgData = (uchar *)m_image.data;
		int k = 0;

		for (int i = 0; i < cDepthHeight; i++)
		{
			for (int j = 0; j < cDepthWidth; j++)
			{
				if (rightHand->m_pHandLineArray[i][j])
				{
					imgData[k++] = 255;
					imgData[k++] = 255;
					imgData[k++] = 255;
				}
				else{
					imgData[k++] = 0;
					imgData[k++] = 0;
					imgData[k++] = 0;
				}
			}
		}
		CvScalar color = cvScalar(0, 255, 0);
		circle(m_image, cvPoint(rightHand->HandCenter.m_depthX, rightHand->HandCenter.m_depthY), 5, color, -1);
		stringstream ss;
		ss << "(";
		ss << rightHand->HandCenter.m_depthX;
		ss << ",";
		ss << rightHand->HandCenter.m_depthY;
		ss << ",";
		ss << rightHand->HandCenter.m_cameraZ;
		ss << ")";
		string msg = ss.str();
		putText(m_image, msg, cvPoint(rightHand->HandCenter.m_depthX, rightHand->HandCenter.m_depthY), 1,1,color);
	}
}

void CVHelper::show()
{
	imshow("Hand", m_image); 
	m_nPressedKey = waitKey(10);
}


int CVHelper::getKeyPressed()
{
	return m_nPressedKey;
}
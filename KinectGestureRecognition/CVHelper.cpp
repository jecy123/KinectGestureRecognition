#include "CVHelper.h"
#include "utils.h"
#include <opencv2\opencv.hpp>
using namespace cv;

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
				if (rightHand->m_pHandAreaArray[i][j])
				{
					imgData[j++] = 255;
					imgData[j++] = 255;
					imgData[j++] = 255;
				}
				else{
					imgData[j++] = 0;
					imgData[j++] = 0;
					imgData[j++] = 0;
				}
			}
		}
		CvScalar color = cvScalar(0, 255, 0);
		circle(m_image, cvPoint(rightHand->HandCenter.m_depthX, rightHand->HandCenter.m_depthY), 5, color, -1);
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
#include "CVHelper.h"
#include "utils.h"
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

void CVHelper::setCursor(int x, int y)
{
	SetCursorPos(x * 5, y * 5);
}

void CVHelper::drawPoint(HandPoint point, Scalar color, int radius)
{
	circle(m_image, cvPoint(point.m_depthX, point.m_depthY), radius, color, -1);
}


void CVHelper::drawLine(HandPoint p1, HandPoint p2, Scalar color)
{
	line(m_image, cvPoint(p1.m_depthX, p1.m_depthY), cvPoint(p2.m_depthX, p2.m_depthY), color, 5);
}


void CVHelper::draw(UINT16 * depthData, Hand * rightHand)
{
	m_image.setTo(0);
	uchar * imgData = (uchar *)m_image.data;
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
		int k = 0;

		for (int i = 0; i < cDepthHeight; i++)
		{
			for (int j = 0; j < cDepthWidth; j++)
			{
				if (rightHand->m_pHandAreaArray[i][j])
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
		//circle(m_image, cvPoint(rightHand->HandCenter.m_depthX, rightHand->HandCenter.m_depthY), 5, color, -1);
		//drawPoint(rightHand->HandCenter);
		//drawPoint(rightHand->HandWrist);
		//drawPoint(rightHand->HandThumb);
		//drawPoint(rightHand->HandTip);

		//drawLine(rightHand->HandCenter, rightHand->HandWrist);
		//drawLine(rightHand->HandCenter, rightHand->HandThumb);
		//drawLine(rightHand->HandCenter, rightHand->HandTip);

		for (int i = 0; i < rightHand->HandFingers.size(); i++)
		{
			drawPoint(rightHand->HandFingers[i], cvScalar(0, 0, 255), 2);

		}

		/*for (int i = 0; i < MAX_IN_FINGER; i++)
		{

			if (rightHand->m_pMin4FingerPoint[i] != nullptr)
			{
				drawPoint(*(rightHand->m_pMin4FingerPoint[i]), cvScalar(0, 255, 255));
			}
		}*/
		//setCursor(rightHand->FingePoint.m_depthX, rightHand->FingePoint.m_depthY);

		gotoXY(0, 2);
		cout << rightHand->HandOutline.size() << endl;
		/*for (int i = 0; i < rightHand->HandOutline.size(); i++)
		{
			drawPoint(rightHand->HandOutline[i], cvScalar(0, 0, 255), 1);
		}*/
		/*stringstream ss;
		ss << "(";
		ss << rightHand->HandCenter.m_depthX;
		ss << ",";
		ss << rightHand->HandCenter.m_depthY;
		ss << ",";
		ss << rightHand->HandCenter.m_cameraZ;
		ss << ")";
		string msg = ss.str();
		putText(m_image, msg, cvPoint(rightHand->HandCenter.m_depthX, rightHand->HandCenter.m_depthY), 1,1,color);*/
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
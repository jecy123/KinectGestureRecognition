#include "Hand.h"
#include <algorithm>



inline bool cmp(HandPoint p1, HandPoint p2)
{
	return p1.m_disFromCenter < p2.m_disFromCenter;
}

Hand::Hand()
{
	initHandArray();
	initVisited();
	maxDis = 0;
}


void Hand::initHandArray()
{
	for (int i = 0; i < cDepthHeight; i++)
	{
		for (int j = 0; j < cDepthWidth; j++)
		{
			m_pHandAreaArray[i][j] = false;
			m_pHandLineArray[i][j] = false; 
			m_pHandOutLineArray[i][j] = false;
		}
	}
}

void Hand::initFingerArray()
{
	for (int i = 0; i < MAX_FINGERCNT; i++)
	{
		m_pMax5FingerPoint[i].m_depthX = 0;
		m_pMax5FingerPoint[i].m_depthY = 0;
		m_pMax5FingerPoint[i].m_cameraZ = 0;
		m_pMax5FingerPoint[i].m_disFromCenter = 0.0;
	}

	for (int i = 0; i < MAX_IN_FINGER; i++)
	{
		m_pMin4FingerPoint[i].m_depthX = 0;
		m_pMin4FingerPoint[i].m_depthY = 0;
		m_pMin4FingerPoint[i].m_cameraZ = 0;
		m_pMin4FingerPoint[i].m_disFromCenter = FLT_MAX;
	}
}

void Hand::refreshHandData(ICoordinateMapper * mapper, CameraSpacePoint pointCenter, CameraSpacePoint pointWrist,UINT16 * depthArray)
{
	initHandArray();
	initFingerArray();
	maxDis = 0;

	this->HandCenter = HandPoint::getHandPoint(mapper, pointCenter);
	this->HandWrist = HandPoint::getHandPoint(mapper, pointWrist);

	//mapper->MapDepthFrameToCameraSpace(cDepthHeight * cDepthWidth, depthArray, cDepthHeight*cDepthWidth, m_points);

	calculateHandRect();

	for (int i = m_leftTopHandPoint.m_depthY; i <= m_rightBottomHandPoint.m_depthY; i++)
	{
		for (int j = m_leftTopHandPoint.m_depthX; j <= m_rightBottomHandPoint.m_depthX; j++)
		{
			int k = i * cDepthWidth + j;
			float CameradepthZ = getCameraZFromDepthXY(mapper, j, i, depthArray[k]);
			if (CameradepthZ >= this->HandCenter.m_cameraZ - threshold && CameradepthZ <= this->HandCenter.m_cameraZ + threshold)
			{
				m_pHandAreaArray[i][j] = true;
			}
			else{
				m_pHandAreaArray[i][j] = false;
			}
		}
	}


	for (int i = m_leftTopHandPoint.m_depthY; i <= m_rightBottomHandPoint.m_depthY; i++)
	{
		for (int j = m_leftTopHandPoint.m_depthX; j <= m_rightBottomHandPoint.m_depthX; j++)
		{
			m_pHandLineArray[i][j] = checkIsOutline(j, i);
			/*if (m_pHandLineArray[i][j] && i <= HandCenter.m_depthY && j <= HandCenter.m_depthX)
			{
				float dis = HandPoint::disBtw2Points(j, i, HandCenter.m_depthX, HandCenter.m_depthY);
				float z = getCameraZFromDepthXY(mapper, j, i, depthArray[i * cDepthWidth + j]);
				HandPoint  p(j, i, z, dis);
				if (m_pMax5FingerPoint[0].m_disFromCenter < dis)
				{
					m_pMax5FingerPoint[4] = m_pMax5FingerPoint[3];
					m_pMax5FingerPoint[3] = m_pMax5FingerPoint[2];
					m_pMax5FingerPoint[2] = m_pMax5FingerPoint[1];
					m_pMax5FingerPoint[1] = m_pMax5FingerPoint[0];

					m_pMax5FingerPoint[0].m_cameraZ = z;
					m_pMax5FingerPoint[0].m_depthX = j;
					m_pMax5FingerPoint[0].m_depthY = i;
					m_pMax5FingerPoint[0].m_disFromCenter = dis;
				}
			}*/


		}
	}


	
	for (int i = m_leftTopHandPoint.m_depthY + 1; i <= m_rightBottomHandPoint.m_depthY - 1; i++)
	{
		for (int j = m_leftTopHandPoint.m_depthX + 1; j <= m_rightBottomHandPoint.m_depthX - 1; j++)
		{
			m_pHandLineArray[i][j] = dealWithOutline(j, i);
		}
	}


	// checkFingerPoint(mapper, depthArray);
}



void Hand::deInitHandOutLine()
{
	for (int i = 0; i < HandOutline.size(); i++)
	{
		HandPoint * point = HandOutline[i];
		if (point!=nullptr)
		{
			delete point;
			point = nullptr;
		}
	}

	HandOutline.clear();
}

Hand::~Hand()
{
	deInitHandOutLine();
}


UINT16 Hand::conventArray(int x, int y, checkType type)
{
	bool(*array)[cDepthHeight][cDepthWidth];
	if (type == TYPE_HAND_AREA)
	{
		array = &m_pHandAreaArray;
	}
	else{
		array = &m_pHandLineArray;
	}
	if ((*array)[y][x])
	{
		return 0x1;
	}
	return 0x0;
}


bool Hand::dealWithOutline(int x, int y)
{
	if (m_pHandLineArray[y][x])
	{
		UINT16 handCheck = 0x0000 |
			conventArray(x, y, TYPE_HAND_OUTLINE) << 8 |
			conventArray(x - 1, y - 1, TYPE_HAND_OUTLINE) << 7 |
			conventArray(x - 1, y, TYPE_HAND_OUTLINE) << 6 |
			conventArray(x - 1, y + 1, TYPE_HAND_OUTLINE) << 5 |
			conventArray(x, y + 1, TYPE_HAND_OUTLINE) << 4 |
			conventArray(x + 1, y + 1, TYPE_HAND_OUTLINE) << 3 |
			conventArray(x + 1, y, TYPE_HAND_OUTLINE) << 2 |
			conventArray(x + 1, y - 1, TYPE_HAND_OUTLINE) << 1 |
			conventArray(x, y - 1, TYPE_HAND_OUTLINE);
		//去除直角点
		if (handCheck & 0x0141 == 0x0141 
			|| handCheck & 0x0101 == 0x0101 
			|| handCheck & 0x0150 == 0x0150 
			|| handCheck & 0x0114 == 0x0114)
		{
			return false;
		}

		int cnt = 0;
		for (int i = 0; i <= 8; i++)
		{
			if ((handCheck >> i) & 0x0001 == 0x0001)
			{
				cnt++;
			}
		}
		if (cnt == 3)
		{
			return true;
		}
		return false;
	}
	
	return false;
}

bool Hand::checkIsOutline(int x, int y)
{
	if (x == 0 || x == cDepthWidth-1||y == 0 || y==cDepthHeight-1)
	{
		return false;
	}
	/*UINT16 handCheck = 0x0000 |
		conventArray(x, y) << 8 |
		conventArray(x - 1, y - 1) << 7 |
		conventArray(x - 1, y) << 6 |
		conventArray(x - 1, y + 1) << 5 |
		conventArray(x, y + 1) << 4 |
		conventArray(x + 1, y + 1) << 3 |
		conventArray(x + 1, y) << 2 |
		conventArray(x + 1, y - 1) << 1 |
		conventArray(x, y - 1);
*/
	UCHAR handCheck = 0x00 |
		conventArray(x, y) << 4 |
		conventArray(x - 1, y) << 3 |
		conventArray(x + 1, y) << 2 |
		conventArray(x, y - 1) << 1 |
		conventArray(x, y + 1);


	if (handCheck == 0x1f || handCheck == 0x00)
	{
		return false;
	}
	return true;
}

float Hand::getCameraZFromDepthXY(ICoordinateMapper * mapper, int x, int y, UINT16 DepthZ)
{
	DepthSpacePoint depthPoint;
	CameraSpacePoint cameraPoint;

	depthPoint.X = (float)x;
	depthPoint.Y = (float)y;

	mapper->MapDepthPointToCameraSpace(depthPoint, DepthZ, &cameraPoint);
	return cameraPoint.Z;

	//return m_points[y * cDepthWidth + x].Z;
}

void Hand::calculateHandRect()
{
	int XOffsetFromCenter = static_cast<int>(40 * (2 - HandCenter.m_cameraZ));
	int YOffsetFromCenter = static_cast<int>(60 * (2 - HandCenter.m_cameraZ));

	m_leftTopHandPoint.m_depthX = max(HandCenter.m_depthX - XOffsetFromCenter, 0);
	m_leftTopHandPoint.m_depthY = max(HandCenter.m_depthY - YOffsetFromCenter, 0);

	m_rightBottomHandPoint.m_depthX = min(HandCenter.m_depthX + XOffsetFromCenter, cDepthWidth - 1);
	m_rightBottomHandPoint.m_depthY = min(HandCenter.m_depthY + YOffsetFromCenter, cDepthHeight - 1);
}


void Hand::initVisited()
{
	for (int i = 0; i < cDepthHeight; i++)
	{
		for (int j = 0; j < cDepthWidth; j++)
		{
			m_visited[i][j] = false;
		}
	}
}

void Hand::checkFingerPoint(ICoordinateMapper * mapper, UINT16 * depthArray)
{
	initVisited();
	deInitHandOutLine();
	//找到第一个轮廓点：
	int x = HandCenter.m_depthX;
	int y = HandCenter.m_depthY;
	while (!m_pHandLineArray[y][x]){
		x--; 
		if (x == 0)
		{
			break;
		}
	}

	if (!m_pHandLineArray[y][x])
	{
		return;
	}
	int nx, ny;

	while (true){

		float z = getCameraZFromDepthXY(mapper, x, y, depthArray[y * cDepthWidth + x]);
		HandPoint *point = new HandPoint(x, y, z);

		HandOutline.push_back(point);

		findNextXY(x, y, nx, ny);
		if (nx == -1 && ny == -1)
		{
			break;
		}
		x = nx;
		y = ny;
	}

}


void Hand::findNextXY(const int & oldX, const int & oldY, int & newX, int & newY)
{
	if (m_pHandLineArray == nullptr)
	{
		return;
	}
	int startX = oldX - 1;
	int startY = oldY - 1;
	
	int endX = oldX - 1;
	int endY = oldY;


	if (oldY == 0)
	{
		//左上边界：
		if (oldX == 0)
		{
			startX = oldX + 1;
			startY = oldY;
			endX = oldX;
			endY = oldY + 1;
		}
		//右上边界：
		else if(oldX == cDepthWidth - 1){
			startX = oldX;
			startY = oldY + 1;
			endX = oldX - 1;
			endY = oldY;
		}
		//上边界：
		else{
			startX = oldX + 1;
			startY = oldY;
			endX = oldX - 1;
			endY = oldY;
		}
	}

	if (oldY == cDepthHeight - 1)
	{
		//左下边界：
		if (oldX == 0)
		{
			startX = oldX;
			startY = oldY - 1;
			endX = oldX + 1;
			endY = oldY;
		}
		//右下边界：
		else if (oldX == cDepthWidth - 1){
			startX = oldX - 1;
			startY = oldY;
			endX = oldX;
			endY = oldY - 1;
		}
		//下边界：
		else{
			startX = oldX - 1;
			startY = oldY;
			endX = oldX + 1;
			endY = oldY;
		}
	}
	
	while (true)
	{
		if (!m_visited[startY][startX] && m_pHandOutLineArray[startY][startX])
		{
			m_visited[startY][startX] = true;
			break;
		}

		m_visited[startY][startX] = true;

		if (startX == endX && startY == endY)
		{
			break;
		}

		if (startY == oldY - 1 && startX < oldX + 1)
		{
			startX++;
		}
		
		if (startX == oldX + 1 && startY < oldY + 1)
		{
			startY++;
		}
		if (startY == oldY + 1 && startX > oldX - 1)
		{
			startX--;
		}
		if (startX == oldX - 1 && startY > oldY - 1)
		{
			startY--;
		}
	}

	if (m_pHandOutLineArray[startY][startX])
	{
		newX = startX;
		newY = startY;
	}
	else
	{
		newX = -1;
		newY = -1;
	}
}
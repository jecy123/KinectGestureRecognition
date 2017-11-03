#include "Hand.h"


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
		}
	}
}

void Hand::refreshHandData(ICoordinateMapper * mapper, CameraSpacePoint point, UINT16 * depthArray)
{
	initHandArray();
	maxDis = 0;

	this->HandCenter = HandPoint::getHandPoint(mapper, point);

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

	for (int i = 0; i < cDepthHeight; i++)
	{
		for (int j = 0; j < cDepthWidth; j++)
		{
			m_pHandLineArray[i][j] = checkIsOutline(j, i);
			if (m_pHandLineArray[i][j]&& i <= HandCenter.m_depthY && j <= HandCenter.m_depthX)
			{
				float dis = HandPoint::disBtw2Points(j, i, HandCenter.m_depthX, HandCenter.m_depthY);
				if (maxDis < dis)
				{
					maxDis = dis;
					FingePoint.m_depthX = j;
					FingePoint.m_depthY = i;
				}
			}
		}
	}

	//checkFingerPoint(mapper, depthArray);
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


UINT16 Hand::conventArray(int x, int y)
{
	if (m_pHandAreaArray[y][x])
	{
		return 0x1;
	}
	return 0x0;
}

bool Hand::checkIsOutline(int x, int y)
{
	if (x == 0 || x == cDepthWidth-1||y == 0 || y==cDepthHeight-1)
	{
		return false;
	}
	UINT16 handCheck = 0x0000 |
		conventArray(x, y) << 8 |
		conventArray(x - 1, y - 1) << 7 |
		conventArray(x - 1, y) << 6 |
		conventArray(x - 1, y + 1) << 5 |
		conventArray(x, y + 1) << 4 |
		conventArray(x + 1, y + 1) << 3 |
		conventArray(x + 1, y) << 2 |
		conventArray(x + 1, y - 1) << 1 |
		conventArray(x, y - 1);

	if (handCheck == 0x01ff || handCheck == 0x0000)
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
	m_rightBottomHandPoint.m_depthY = min(HandCenter.m_depthY + XOffsetFromCenter, cDepthHeight - 1);
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
		if (!m_visited[startY][startX] && m_pHandLineArray[startY][startX])
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

	if (m_pHandLineArray[startY][startX])
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
#include "Hand.h"


Hand::Hand()
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

void Hand::refreshHandCenter(ICoordinateMapper * mapper, CameraSpacePoint point, UINT16 * depthArray)
{
	this -> HandCenter = HandPoint::getHandPoint(mapper, point);

	calculateXYOffset();

	for (int i = HandCenter.m_depthY - m_nYOffsetFromCenter; i < cDepthHeight && i <= HandCenter.m_depthY + m_nYOffsetFromCenter; i++)
	{
		for (int j = HandCenter.m_depthX - m_nXOffsetFromCenter; j < cDepthWidth && j <= HandCenter.m_depthX + m_nXOffsetFromCenter; j++)
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
}


Hand::~Hand()
{
}



float Hand::getCameraZFromDepthXY(ICoordinateMapper * mapper, int x, int y, UINT16 DepthZ)
{
	DepthSpacePoint depthPoint;
	CameraSpacePoint cameraPoint;

	depthPoint.X = (float)x;
	depthPoint.Y = (float)y;

	mapper->MapDepthPointToCameraSpace(depthPoint, DepthZ, &cameraPoint);
	return cameraPoint.Z;
}

void Hand::calculateXYOffset()
{
	m_nXOffsetFromCenter = static_cast<int>(40 * (2 - HandCenter.m_cameraZ));
	m_nYOffsetFromCenter = static_cast<int>(60 * (2 - HandCenter.m_cameraZ));
}

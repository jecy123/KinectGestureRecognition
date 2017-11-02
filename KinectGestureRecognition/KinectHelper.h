#pragma once
#include <Kinect.h>
#include "Hand.h"
#include "CVHelper.h"

class KinectHelper
{
public:

	KinectHelper();
	virtual ~KinectHelper();

	static void Run();
	HRESULT init();
	void	deInit();
	HRESULT UpdateFrame();
	HRESULT UpdateDepthData();
	HRESULT UpdateBodyData();
private:
	HRESULT initDepth();
	HRESULT initBody();

	IKinectSensor *			m_pKinectSensor;
	ICoordinateMapper *		m_pCoordinateMapper;
	IDepthFrameReader *		m_pDepthFrameReader;
	IBodyFrameReader *		m_pBodyReader;

	UINT16 *				m_pDepthArray;
	Hand *					m_pRightHand;
	CVHelper *				m_pCVHelper;
protected:
	virtual void onInit(){};
	virtual void onDepthDataArrived(){};
	virtual void onBodyDataArrived(){};
	virtual void onDestroy(){};
};

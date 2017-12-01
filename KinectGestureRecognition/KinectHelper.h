#pragma once
#include "dllapi.h"
#include "utils.h"
#include "Hand.h"
#include "CVHelper.h"
#include "GestureRecgnition.h"

class DLL_API KinectHelper
{
public:

	KinectHelper();
	virtual ~KinectHelper();

	void setGestureEventHandler(GestureEventHandler * pEventHandler);

	static void Run();
	HRESULT init();
	void	deInit();
	HRESULT UpdateFrame();
	HRESULT UpdateDepthData();
	HRESULT UpdateBodyData();
	GestureEventHandler * m_pEventHandler;
	
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
	GestureRecgnition *		m_pGestureRecgnition;

protected:
	virtual void onInit(){};
	virtual void onDepthDataArrived(){};
	virtual void onBodyDataArrived(){};
	virtual void onDestroy(){};
};


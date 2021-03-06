#include "KinectHelper.h"
#include "utils.h"
#include "HandEventsHandler.h"


void KinectHelper::Run()
{
	KinectHelper k;
	k.init();
	k.UpdateFrame();
	k.deInit();
}


void KinectHelper::setGestureRecgnition(GestureRecgnition * pGestureRecgnition)
{
	this->m_pGestureRecgnition = pGestureRecgnition;
}


void KinectHelper::setGestureEvent(GestureEvents * pEventHandler)
{
	this->m_pEventHandler = pEventHandler;
	this->m_pGestureRecgnition->setGestureEventsHandler(pEventHandler);
}

HRESULT KinectHelper::UpdateFrame()
{
	HRESULT hr = S_OK;
	while (true)
	{
		
		hr = UpdateDepthData();
		hr = UpdateBodyData();	

		if (m_pCVHelper != nullptr && m_pDepthArray != nullptr /*&& m_pRightHand != nullptr*/)
		{
			m_pCVHelper->draw(m_pDepthArray, m_pRightHand);
			m_pCVHelper->show();
			if (m_pCVHelper->getKeyPressed() == VK_ESCAPE)
			{
				break;
			}
		}

		if (m_pGestureRecgnition != nullptr)
		{
			m_pGestureRecgnition->update(m_pRightHand);
		}
	}
	return hr;
}

HRESULT KinectHelper::UpdateDepthData()
{
	if (!m_pKinectSensor || !m_pDepthFrameReader)
	{
		return E_POINTER;
	}

	HRESULT hr = -1;
	IDepthFrame * pDepthFrame = nullptr;
	hr = m_pDepthFrameReader->AcquireLatestFrame(&pDepthFrame);
	
	if (SUCCEEDED(hr))
	{
		//cout << "成功获取到深度数据！" << endl;
		hr = pDepthFrame->CopyFrameDataToArray(cDepthHeight * cDepthWidth, m_pDepthArray);
		
	}
	SafeRealease(pDepthFrame);
	return hr;
}


HRESULT KinectHelper::UpdateBodyData()
{
	if (!m_pKinectSensor || !m_pDepthFrameReader)
	{
		return E_POINTER;
	}

	HRESULT hr = -1;
	IBodyFrame * pBodyFrame = nullptr;
	hr = m_pBodyReader->AcquireLatestFrame(&pBodyFrame);
	if (SUCCEEDED(hr))
	{
		IBody * pBody[BODY_COUNT] = { 0 };
		hr = pBodyFrame->GetAndRefreshBodyData(BODY_COUNT, pBody);

		if (SUCCEEDED(hr))
		{
			BOOLEAN bTracked = FALSE;
			for (int i = 0; i < BODY_COUNT; i++)
			{
				hr = pBody[i]->get_IsTracked(&bTracked);
				if (SUCCEEDED(hr) && bTracked)
				{
					if (NULL != pBody[i])
					{
						//cout << i << endl;
						//Joint joints[JointType_Count];
						//pBody[i]->GetJoints(JointType_Count, joints);
						m_pRightHand->refreshHandData(m_pCoordinateMapper, pBody[i], m_pDepthArray);
						//m_pRightHand->refreshHandData(m_pCoordinateMapper, joints,  m_pDepthArray);
					}
				}
			}
		}
	}
	SafeRealease(pBodyFrame);
	return hr;
}

HRESULT KinectHelper::init()
{
	HRESULT hr = GetDefaultKinectSensor(&m_pKinectSensor);
	if (FAILED(hr))
	{
		return hr;
	}

	if (m_pKinectSensor)
	{
		hr = m_pKinectSensor->Open();
		
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_CoordinateMapper(&m_pCoordinateMapper);
		}
		if (SUCCEEDED(hr))
		{
			hr = initBody();
		}
		if (SUCCEEDED(hr))
		{
			hr = initDepth();
		}

		if (!m_pKinectSensor || FAILED(hr))
		{
			cout << "初始化Kinect失败！" << endl;
			return E_FAIL;
		}
		cout << "初始化Kinect成功！" << endl;
	}

	m_pDepthArray = new UINT16[cDepthHeight * cDepthWidth];
	m_pCVHelper = new CVHelper;
	m_pGestureRecgnition = new GestureRecgnition;
	m_pRightHand = new Hand;

	//m_pEventHandler = new HandEventsHandler;
	//m_pGestureRecgnition->setGestureEventsHandler(m_pEventHandler);
	return hr;
}


HRESULT KinectHelper::initBody()
{
	IBodyFrameSource *pBodyFrameSource = nullptr;
	HRESULT hr = -1;
	if (m_pKinectSensor)
	{
		hr = m_pKinectSensor->get_BodyFrameSource(&pBodyFrameSource);
		if (SUCCEEDED(hr))
		{
			hr = pBodyFrameSource->OpenReader(&m_pBodyReader);
		}
	}
	SafeRealease(pBodyFrameSource);
	return hr;
}

HRESULT KinectHelper::initDepth()
{
	IDepthFrameSource * pDepthFrameSource = nullptr;
	HRESULT hr = -1;
	if (m_pKinectSensor)
	{
		hr = m_pKinectSensor->get_DepthFrameSource(&pDepthFrameSource);
		if (SUCCEEDED(hr))
		{
			hr = pDepthFrameSource->OpenReader(&m_pDepthFrameReader);
		}
	}
	SafeRealease(pDepthFrameSource);
	return hr;
}


void KinectHelper::deInit()
{
	cout << "DeInit processing..." << endl;
	BOOLEAN isOpened;
	m_pKinectSensor->get_IsOpen(&isOpened);
	if (isOpened)
	{
		m_pKinectSensor->Close();
	}

	SafeRealease(m_pKinectSensor);
	SafeRealease(m_pCoordinateMapper);
	SafeRealease(m_pDepthFrameReader);
	SafeRealease(m_pBodyReader);
	
	if (m_pDepthArray != nullptr)
	{
		delete[] m_pDepthArray;
	}

	if (m_pRightHand != nullptr)
	{
		delete m_pRightHand;
	}

	if (m_pCVHelper != nullptr)
	{
		delete m_pCVHelper;
	}

	if (m_pGestureRecgnition != nullptr)
	{
		delete m_pGestureRecgnition;
	}

	if (m_pEventHandler != nullptr)
	{
		delete m_pEventHandler;
	}

}

KinectHelper::KinectHelper()
{
	m_pKinectSensor = nullptr;
	m_pCoordinateMapper = nullptr;
	m_pDepthFrameReader = nullptr; 
	m_pBodyReader = nullptr;
	m_pRightHand = nullptr;
	m_pDepthArray = nullptr;
	m_pCVHelper = nullptr;
	m_pEventHandler = nullptr;
}


KinectHelper::~KinectHelper()
{
}

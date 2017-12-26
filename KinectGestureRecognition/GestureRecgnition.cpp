#define DLL_IMPLEMENT

#include "GestureRecgnition.h"
#include "utils.h"

#define PI       3.14159265358979323846

GestureRecgnition::GestureRecgnition()
{
	leftHand = rightHand = nullptr;
	eventHandler = nullptr;
	isTickCountStart = false;
	m_lastType = m_type = TYPE_UNKNOWN;
	isfirstGetGesture = false;

	args = new GestureArgs;

	file.open("D:\\data.txt");
}

GestureRecgnition::~GestureRecgnition()
{
	delete args;
	file.close();
}


void GestureRecgnition::start(Hand * hand)
{

}


void GestureRecgnition::setGestureEventsHandler(GestureEventHandler * handler)
{
	this->eventHandler = handler;
}

void GestureRecgnition::doGestureEvent()
{
//	gotoXY(0, 15);
//	cout << "                       ";
//	gotoXY(0, 15);
	if (m_type == TYPE_ONE_FINGER)
	{
		if (currentArgs.vz < cFingerTouchZ)
		{
			onFingerTouch(&currentArgs);
			if (this->eventHandler!=nullptr)
			{
				this->eventHandler->onOneFingerTouch(&currentArgs);
			}
		}
		else
		{
			onFingerMove(&currentArgs);
			if (this->eventHandler!=nullptr)
			{
				this->eventHandler->onOneFingerMove(&currentArgs);
			}
		}
	}
	else if (m_type == TYPE_HOLD)
	{
		if (m_lastType == TYPE_OPEN)
		{
			onGrab(&currentArgs);
			if (this->eventHandler != nullptr)
			{
				this->eventHandler->onHandGrab(&currentArgs);
			}
		}
		else{
			if (currentArgs.vz < cFistPushZ)
			{
				onFistPush(&currentArgs);
				if (this->eventHandler != nullptr)
				{
					this->eventHandler->onHandHoldPush(&currentArgs);
				}
			}
			else if (currentArgs.vz > cFistPullZ)
			{
				onFistPull(&currentArgs);
				if (this->eventHandler != nullptr)
				{
					this->eventHandler->onHandHoldPull(&currentArgs);
				}
			}
			else
			{
				onFistMove(&currentArgs);
				if (this->eventHandler != nullptr)
				{
					this->eventHandler->onHandHoldMove(&currentArgs);
				}
			}

		}
	}
	else if (m_type == TYPE_OPEN)
	{
		//cout << "Hand move!" << endl;
		if (m_lastType == TYPE_HOLD)
		{
			onRelease(&currentArgs);
			if (this->eventHandler != nullptr)
			{
				this->eventHandler->onHandRelease(&currentArgs);
			}
		}
		else{

			if (currentArgs.vz < cHandPushZ)
			{
				onHandPush(&currentArgs);
				//cout << "Hand push!" << endl;
				if (this->eventHandler != nullptr)
				{
					this->eventHandler->onHandPush(&currentArgs);
				}
			}
			else if (currentArgs.vz > cFistPullZ)
			{
				onHandPull(&currentArgs);
				//cout << "Hand pull!" << endl;
				if (this->eventHandler != nullptr)
				{
					this->eventHandler->onHandPull(&currentArgs);
				}
			}
			else{
				cout << "MOVE!!" << endl;
				onHandMove(&currentArgs);
				if (this->eventHandler != nullptr)
				{
					this->eventHandler->onHandMove(&currentArgs);
				}
			}

		}
	}

	gotoXY(0, 6);
	
	/*cout << "x = " << currentArgs.x << "          " << endl;
	cout << "y = " << currentArgs.y << "          " << endl;
	cout << "z = " << currentArgs.z << "          " << endl;

	cout << "vx = " << currentArgs.vx << "          " << endl;
	cout << "vy = " << currentArgs.vy << "          " << endl;
	cout << "vz = " << currentArgs.vz << "          " << endl;*/
}

void GestureRecgnition::recgnition()
{
	if (isTickCountStart)
	{
		startTick();
		if (currentTime != lastTime)
		{
			bool isStarted = lastArgs.x != 0 && lastArgs.y != 0 && lastArgs.z != 0;
			if (isStarted)
			{
				ULONG timeInterval = currentTime - lastTime;

				currentArgs.vx = (currentArgs.x - lastArgs.x) / timeInterval;
				currentArgs.vy = (currentArgs.y - lastArgs.y) / timeInterval;
				currentArgs.vz = (currentArgs.z - lastArgs.z) / timeInterval;

				currentArgs.dx = currentArgs.x - lastArgs.x;
				currentArgs.dy = currentArgs.y - lastArgs.y;
			
				doGestureEvent();
			}
		}
	}
}

void GestureRecgnition::refresh(Hand * leftHand, Hand * rightHand)
{
	this->rightHand = rightHand;
	this->leftHand = leftHand;
	m_lastType = m_type;
	if (isfirstGetGesture == true)
	{
		if (rightHand->m_handState == HandState_NotTracked || rightHand->m_handState == HandState_Unknown)
		{
			m_type = TYPE_UNKNOWN;

			isfirstGetGesture = false;
			lastTime = 0;
			currentTime = 0;

			args->reset();
			lastArgs.reset();
			currentArgs.reset();
		}
		else{
			changeState();
		}
	}
	else
	{
		if (rightHand->m_handState == HandState_Open)
		{
			isfirstGetGesture = true;
			m_type = TYPE_OPEN;
			lastTime = 0;
			currentTime = 0;

			args->reset();
			lastArgs.reset();
			currentArgs.reset();
		}
		else if (rightHand->m_handState == HandState_Closed)
		{
			isfirstGetGesture = true;
			m_type = TYPE_HOLD;
			lastTime = 0;
			currentTime = 0;

			args->reset();
			lastArgs.reset();
			currentArgs.reset();
		}
		else if (rightHand->m_handState == HandState_Lasso)
		{
			isfirstGetGesture = true;
			m_type = TYPE_ONE_FINGER;
			lastTime = 0;
			currentTime = 0;

			args->reset();
			lastArgs.reset();
			currentArgs.reset();
		}
		else{
			isfirstGetGesture = false;
		}
	} 
}

void GestureRecgnition::changeState()
{
	tickUp();
	gotoXY(0, 4);

	cout << "x = " << currentArgs.x << "    tipX = " << currentArgs.tipX << endl;
	cout << "y = " << currentArgs.y << "    tipY = " << currentArgs.tipY << endl;
	cout << "z = " << currentArgs.z << "    tipZ = " << currentArgs.tipZ << endl;

	cout << "vx = " << currentArgs.vx << "          " << endl;
	cout << "vy = " << currentArgs.vy << "          " << endl;
	cout << "vz = " << currentArgs.vz << "          " << endl;

	//gotoXY(0, 13);
	cout << "retain time = " << currentArgs.retainTime << "    " << endl;
	cout << "zoom time = " << currentArgs.zoomTime << "    " << endl;
	cout << "isRetain = " << currentArgs.isRetain << endl;
	cout << "isSwip = " << currentArgs.isSwip << endl;
	//cout << "zoomArgs = " << currentArgs.zoomArgs.a <<"                "<< endl;
	//cout << "curvity = " << currentArgs.curvity << "    " << endl;
	//cout << "disCenterTip = " << currentArgs.disCenterTip << "    " << endl;
	/*if (currentArgs.zoomTime != 0)
	{
		file << setw(6) << currentArgs.zoomTime << setw(10) << currentArgs.curvity << endl;

	}
	else{
		file << endl;
	}*/
	if (m_type == TYPE_OPEN)
	{
		gotoXY(0, 17);
		cout << "OPEN             ";
		if (currentArgs.isZoom)
		{
			m_type = TYPE_ZOOM;
		}
		if (currentArgs.isRetain)
		{
			m_type = TYPE_OPEN_RETAIN;
			
		}
		else if (currentArgs.isSwip)
		{

			m_type = TYPE_OPEN_SWIP;
		}
		else if (this->rightHand->m_handState == HandState_Closed)
		{
			m_type = TYPE_GRAB;
		}
		else
		{
			if (currentArgs.isMove){
				m_type = TYPE_OPEN_MOVE;
			}
		}
	}
	if (m_type == TYPE_OPEN_MOVE)
	{
		gotoXY(0, 17);
		cout << "MOVE         "; 
		if (currentArgs.isZoom)
		{
			m_type = TYPE_ZOOM;
		}
		if (currentArgs.retainTime >= 100)
		{
			m_type = TYPE_OPEN;
		}
		if (currentArgs.isSwip)
		{
			m_type = TYPE_OPEN_SWIP;
		}
	}
	if (m_type == TYPE_OPEN_RETAIN)
	{
		gotoXY(0, 17);
		cout << "RETAIN        ";
		if (currentArgs.isZoom)
		{
			m_type = TYPE_ZOOM;
		}

		if (currentArgs.isSwip)
		{
			m_type = TYPE_OPEN_SWIP;
		}
		else if (currentArgs.retainTime <= 2000)
		{
			if (currentArgs.vz < -5)
			{
				m_type = TYPE_OPEN_CLICK;
			}
			else if (currentArgs.isMove)
			{
				m_type = TYPE_OPEN_RETAIN_MOVE;
			}
		}
		else{
			m_type = TYPE_OPEN;
		}
	}
	if (m_type == TYPE_OPEN_SWIP)
	{
		gotoXY(0, 17);
		cout << "SWIP            ";
		if (!currentArgs.isSwip)
		{
			m_type = TYPE_OPEN;
		}
		if (currentArgs.isMove)
		{
			m_type = TYPE_OPEN_MOVE;
		}
	}
	if (m_type == TYPE_GRAB)
	{
		gotoXY(0, 17);
		cout << "GRAB              ";
		if (currentArgs.isMove)
		{
			m_type = TYPE_HOLD_MOVE;
		}
		else if (currentArgs.isSwip)
		{
			m_type = TYPE_DRAG;
		}
	}
	if (m_type == TYPE_OPEN_CLICK)
	{
		gotoXY(0, 17);
		cout << "         CLICK            ";
		if (currentArgs.retainTime >= 50)
			m_type = TYPE_OPEN; 
	}
	if (m_type == TYPE_OPEN_RETAIN_MOVE)
	{

		gotoXY(0, 17);
		cout << "RETAIN MOVE              ";
		if (currentArgs.retainTime >= 400)
		{
			m_type = TYPE_OPEN;
		}
	}
	if (m_type == TYPE_ZOOM)
	{

		gotoXY(0, 17);
		if (currentArgs.zoomArgs.a > 0)
		{
			cout << "ZOOM IN              ";
		}
		else{
			cout << "ZOOM OUT             ";
		}

		if (!currentArgs.isZoom)
		{
			m_type = TYPE_OPEN;
		}
	}

}

void GestureRecgnition::update(Hand * hand)
{
	string s;
	this->rightHand = hand;
	//先记录一下更新状态之前的m_type
	m_lastType = m_type;
	switch (hand->m_handState)
	{
	case HandState_Open:
		s = "Open      "; 
		startTimer();
		m_type = TYPE_OPEN;
		break;
	case HandState_Closed:
		s = "Closed    ";
		startTimer();
		m_type = TYPE_HOLD;
		break;
	case HandState_Lasso:
		s = "OneFinger ";
		startTimer();
		m_type = TYPE_ONE_FINGER;
		break;
	case HandState_NotTracked:
		resetTimer();
		m_type = TYPE_UNKNOWN;
		s = "NotTracked ";
		break;
	case HandState_Unknown:
		resetTimer();
		m_type = TYPE_UNKNOWN;
		s = "UnKnown    ";
		break;
	}

	recgnition();
	/*gotoXY(0, 3);
	cout << s;
	gotoXY(0, 4);
	cout << lastTime << "          ";
	gotoXY(0, 5);
	cout << currentTime << "          ";*/
}

GestureType GestureRecgnition::getType()
{
	return m_type;
}

void GestureRecgnition::setType(GestureType type)
{
	this->m_type = type;
}


void GestureRecgnition::resetTimer()
{
	if (isTickCountStart == true)
	{
		lastTime = 0;
		currentTime = 0;

		args->reset();
		lastArgs.reset();
		currentArgs.reset();

		isTickCountStart = false;
	}
}

void GestureRecgnition::startTimer()
{
	if (isTickCountStart == false)
	{
		lastTime = 0;
		currentTime = 0;

		args->reset();
		lastArgs.reset();
		currentArgs.reset();
		isTickCountStart = true;
	}

}


void GestureRecgnition::startTick()
{
	lastTime = currentTime;
	currentTime = getTickCounts();

	lastArgs = currentArgs;

	if (rightHand != nullptr)
	{
		if (m_type == TYPE_ONE_FINGER || m_type == TYPE_ONE_FINGER_RETAIN)
		{

			currentArgs.setXYZ(
				rightHand->FingerTip.m_depthX,
				rightHand->FingerTip.m_depthY,
				rightHand->FingerTip.m_cameraZ * 1000);
		}
		else{
			currentArgs.setXYZ(
				rightHand->HandCenter.m_depthX,
				rightHand->HandCenter.m_depthY,
				rightHand->HandCenter.m_cameraZ * 1000);
		}
	}
}


void GestureRecgnition::tickUp()
{
	lastTime = currentTime;
	currentTime = getTickCounts();

	//lastArgs = currentArgs;

	if (rightHand != nullptr)
	{
		if (m_type == TYPE_ONE_FINGER || m_type == TYPE_ONE_FINGER_RETAIN)
		{
			args->setXYZ(
				leftHand->HandTip.m_depthX,
				leftHand->HandTip.m_depthY,
				leftHand->HandTip.m_cameraZ * 1000,
				rightHand->HandTip.m_depthX,
				rightHand->HandTip.m_depthY,
				rightHand->HandTip.m_cameraZ * 1000, currentTime);

			/*currentArgs.setXYZ(
				rightHand->HandTip.m_depthX,
				rightHand->HandTip.m_depthY,
				rightHand->HandTip.m_cameraZ * 1000, currentTime);*/
		}
		else{

			args->setXYZ(
				leftHand->HandCenter.m_depthX,
				leftHand->HandCenter.m_depthY,
				leftHand->HandCenter.m_cameraZ * 1000,
				rightHand->HandCenter.m_depthX,
				rightHand->HandCenter.m_depthY,
				rightHand->HandCenter.m_cameraZ * 1000, currentTime);

			args->setTipXYZ(
				leftHand->HandTip.m_depthX,
				leftHand->HandTip.m_depthY,
				leftHand->HandTip.m_cameraZ * 1000,
				rightHand->HandTip.m_depthX,
				rightHand->HandTip.m_depthY,
				rightHand->HandTip.m_cameraZ * 1000);
			args->calculateCurvity();

			//currentArgs.setXYZ(
			//	rightHand->HandCenter.m_depthX,
			//	rightHand->HandCenter.m_depthY,
			//	rightHand->HandCenter.m_cameraZ * 1000);

			//currentArgs.setTipXYZ(
			//	rightHand->HandTip.m_depthX,
			//	rightHand->HandTip.m_depthY,
			//	rightHand->HandTip.m_cameraZ * 1000);
			//currentArgs.calculateCurvity(currentTime);
			//currentArgs.setCos(HandPoint::cosin3d(hand->HandCenter, hand->HandWrist, hand->HandTip));
		}
	}

	//if (currentTime != lastTime)
	//{
	//	bool isStarted = lastArgs.x != 0 && lastArgs.y != 0 && lastArgs.z != 0;
	//	if (isStarted)
	//	{
	//		ULONG timeInterval = currentTime - lastTime;

	//		int dx = currentArgs.x - lastArgs.x;
	//		int dy = currentArgs.y - lastArgs.y;
	//		int dz = currentArgs.z - lastArgs.z;
	//		currentArgs.setDxDyDz(dx, dy, dz, timeInterval);

	//		double interval = (double)timeInterval;
	//		double vx = dx / interval * 100;
	//		double vy = dy / interval * 100;
	//		double vz = dz / interval * 100;

	//		currentArgs.setVxVyVz(vx, vy, vz);
	//	}
	//}
}
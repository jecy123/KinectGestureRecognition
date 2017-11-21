#include "GestureRecgnition.h"
#include "utils.h"


GestureRecgnition::GestureRecgnition()
{
	hand = nullptr;
	eventHandler = nullptr;
	isTickCountStart = false;
}

GestureRecgnition::~GestureRecgnition()
{
}


void GestureRecgnition::start(Hand * hand)
{

}


void GestureRecgnition::setGestureEventsHandler(GestureEvents * handler)
{
	this->eventHandler = handler;
}

void GestureRecgnition::doGestureEvent()
{
	gotoXY(0, 15);
	cout << "                       ";
	gotoXY(0, 15);
	if (m_type == TYPE_ONE_FINGER)
	{
		if (currentArgs.vz < -0.65)
		{
			cout << "Finger Touch!" << endl;
			if (this->eventHandler!=nullptr)
			{
				this->eventHandler->onOneFingerTouch(&currentArgs);
			}
		}
		else{
			//cout << "Finger Moved!" << endl;
			if (this->eventHandler!=nullptr)
			{
				this->eventHandler->onOneFingerMove(&currentArgs);
			}
		}
	}
	else if (m_type == TYPE_HOLD)
	{
		cout << "Hold move!" << endl; 
		if (this->eventHandler != nullptr)
		{
			this->eventHandler->onHandHoldMove(&currentArgs);
		}
		if (currentArgs.vz < -0.7)
		{
			cout << "Hold push!" << endl;
			if (this->eventHandler != nullptr)
			{
				this->eventHandler->onHandHoldPush(&currentArgs);
			}
		}
		else if (currentArgs.vz > 0.7)
		{
			cout << "Hold pull!" << endl;
			if (this->eventHandler != nullptr)
			{
				this->eventHandler->onHandHoldPull(&currentArgs);
			}
		}
	}
	else if (m_type == TYPE_OPEN)
	{
		cout << "Hand move!" << endl;
		if (this->eventHandler != nullptr)
		{
			this->eventHandler->onHandMove(&currentArgs);
		}
		if (currentArgs.vz < -1)
		{
			cout << "Hand push!" << endl;
			if (this->eventHandler != nullptr)
			{
				this->eventHandler->onHandPush(&currentArgs);
			}
		}
		else if (currentArgs.vz > 1)
		{
			cout << "Hand pull!" << endl;
			if (this->eventHandler != nullptr)
			{
				this->eventHandler->onHandPull(&currentArgs);
			}
		}
	}
	/*switch (m_type)
	{
	case TYPE_ONE_FINGER:

		break;
	case TYPE_OPEN:
		break;
	case TYPE_HOLD:
		break;
	case TYPE_ONE_FINGER_RETAIN:
		break;
	case TYPE_UNKNOWN:
		break;
	default:
		break;
	}*/

	gotoXY(0, 6);
	
	cout << "x = " << currentArgs.x << "          " << endl;
	cout << "y = " << currentArgs.y << "          " << endl;
	cout << "z = " << currentArgs.z << "          " << endl;

	cout << "vx = " << currentArgs.vx << "          " << endl;
	cout << "vy = " << currentArgs.vy << "          " << endl;
	cout << "vz = " << currentArgs.vz << "          " << endl;
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
				double timeInterval = (double)(currentTime - lastTime);

				currentArgs.vx = (double)(currentArgs.x - lastArgs.x) / timeInterval;
				currentArgs.vy = (double)(currentArgs.y - lastArgs.y) / timeInterval;
				currentArgs.vz = (double)(currentArgs.z - lastArgs.z) / timeInterval;
				
				doGestureEvent();
			}
		}
	}
}


void GestureRecgnition::update(Hand * hand)
{
	string s;
	this->hand = hand;
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
	gotoXY(0, 3);
	cout << s;
	gotoXY(0, 4);
	cout << lastTime << "          ";
	gotoXY(0, 5);
	cout << currentTime << "          ";
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

	if (hand != nullptr)
	{
		if (m_type == TYPE_ONE_FINGER || m_type == TYPE_ONE_FINGER_RETAIN)
		{

			currentArgs.setXYZ(
				hand->HandTip.m_depthX,
				hand->HandTip.m_depthY,
				hand->HandTip.m_cameraZ * 1000);
		}
		else{
			currentArgs.setXYZ(
				hand->HandCenter.m_depthX,
				hand->HandCenter.m_depthY,
				hand->HandCenter.m_cameraZ * 1000);
		}
	}
}
#pragma once
#include "Hand.h"
#include "dllapi.h"
#include "GestureArgs.h"
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

//手势识别的接口类
class DLL_API GestureEventHandler
{
public:
	GestureEventHandler(){}
	virtual ~GestureEventHandler(){}
	virtual void onOneFingerMove(HandArgs * args){}
	virtual void onOneFingerTouch(HandArgs * args){}
	virtual void onHandMove(HandArgs * args){}
	virtual void onHandPush(HandArgs * args){}
	virtual void onHandPull(HandArgs * args){}
	virtual void onHandHoldMove(HandArgs * args){}
	virtual void onHandHoldPush(HandArgs * args){}
	virtual void onHandHoldPull(HandArgs * args){}
	virtual void onHandGrab(HandArgs * args){}
	virtual void onHandRelease(HandArgs * args){}
};

enum DLL_API GestureType
{
	TYPE_ONE_FINGER,
	TYPE_ONE_FINGER_RETAIN,
	TYPE_OPEN,
	TYPE_OPEN_RETAIN,
	TYPE_OPEN_RETAIN_MOVE,
	TYPE_OPEN_CLICK,
	TYPE_OPEN_MOVE,
	TYPE_OPEN_SWIP,
	TYPE_HOLD,
	TYPE_HOLD_MOVE,
	TYPE_UNKNOWN,
	TYPE_GRAB,
	TYPE_RELEASE,
	TYPE_DRAG,
	TYPE_ZOOM
};

class DLL_API GestureRecgnition
{
public:
	GestureRecgnition();
	~GestureRecgnition();

	void start(Hand * hand);
	void refresh(Hand * leftHand, Hand * rightHand);
	void update(Hand * hand);
	void changeState();

	void tickUp();

	void recgnition();
	GestureType getType();

	void setGestureEventsHandler(GestureEventHandler * handler);
	void setType(GestureType type);
	virtual void onFingerMove(HandArgs * args){}
	virtual void onFingerTouch(HandArgs * args){}

	virtual void onGrab(HandArgs * args){}
	virtual void onRelease(HandArgs * args){}
	
	virtual void onHandMove(HandArgs * args){}
	virtual void onHandPush(HandArgs * args){}
	virtual void onHandPull(HandArgs * args){}
	
	virtual void onFistMove(HandArgs * args){}
	virtual void onFistPush(HandArgs * args){}
	virtual void onFistPull(HandArgs * args){}
	
private:
	bool isfirstGetGesture;

	ofstream file;

	GestureType m_type;
	GestureType m_lastType;

	GestureEventHandler * eventHandler;
	Hand * rightHand;
	Hand * leftHand;
	ULONG currentTime;
	ULONG lastTime;


	
	HandArgs currentArgs;
	HandArgs lastArgs;

	GestureArgs * args;

	int startX, startY, startZ;
	int endX, endY, endZ;
	double time;
	bool isTickCountStart;
	void resetTimer();
	void startTimer();
	void startTick();
	void doGestureEvent();
};


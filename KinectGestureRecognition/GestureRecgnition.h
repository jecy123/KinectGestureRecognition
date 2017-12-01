#pragma once
#include "Hand.h"
#include "dllapi.h"

typedef struct _GestureArgs
{
	int x;
	int y;
	float z;

	double vx;
	double vy;
	double vz;
	_GestureArgs()
	{
		reset();
	}
	void reset()
	{
		x = y = 0;
		z = 0.0;
		vx = vy = vz = 0.0;
	}

	void setXYZ(int x, int y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
}GestureArgs;


class DLL_API GestureEventHandler
{
public:
	virtual void onOneFingerMove(GestureArgs * args) = 0;
	virtual void onOneFingerTouch(GestureArgs * args) = 0;
	virtual void onHandMove(GestureArgs * args) = 0;
	virtual void onHandPush(GestureArgs * args) = 0;
	virtual void onHandPull(GestureArgs * args) = 0;
	virtual void onHandHoldMove(GestureArgs * args) = 0;
	virtual void onHandHoldPush(GestureArgs * args) = 0;
	virtual void onHandHoldPull(GestureArgs * args) = 0;
};

enum DLL_API GestureType
{
	TYPE_ONE_FINGER,
	TYPE_OPEN,
	TYPE_HOLD,
	TYPE_ONE_FINGER_RETAIN,
	TYPE_UNKNOWN
};

class DLL_API GestureRecgnition
{
public:
	GestureRecgnition();
	~GestureRecgnition();

	void start(Hand * hand);
	void update(Hand * hand);
	void recgnition();
	GestureType getType();

	void setGestureEventsHandler(GestureEventHandler * handler);
	void setType(GestureType type);
private:
	GestureType m_type;

	GestureEventHandler * eventHandler;
	Hand * hand;
	ULONG currentTime;
	ULONG lastTime;

	GestureArgs currentArgs;
	GestureArgs lastArgs;

	int startX, startY, startZ;
	int endX, endY, endZ;
	double time;
	bool isTickCountStart;
	void resetTimer();
	void startTimer();
	void startTick();
	void doGestureEvent();
};


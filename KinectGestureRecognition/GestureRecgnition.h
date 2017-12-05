#pragma once
#include "Hand.h"

typedef struct _GestureArgs
{
	int x;
	int y;
	float z;

	double vx;
	double vy;
	double vz;

	int dx;
	int dy;

	_GestureArgs()
	{
		reset();
	}
	void reset()
	{
		x = y = 0;
		z = 0.0;
		vx = vy = vz = 0.0;
		dx = dy = 0;
	}

	void setXYZ(int x, int y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
}GestureArgs;


class GestureEvents
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
	virtual void onHandGrab(GestureArgs * args) = 0;
	virtual void onHandRelease(GestureArgs * args) = 0;
};

enum GestureType
{
	TYPE_ONE_FINGER,
	TYPE_OPEN,
	TYPE_HOLD,
	TYPE_ONE_FINGER_RETAIN,
	TYPE_UNKNOWN
};

class GestureRecgnition
{
public:
	GestureRecgnition();
	~GestureRecgnition();

	void start(Hand * hand);
	void update(Hand * hand);
	void recgnition();
	GestureType getType();

	void setGestureEventsHandler(GestureEvents * handler);
	void setType(GestureType type);
private:
	GestureType m_type;
	GestureType m_lastType;

	GestureEvents * eventHandler;
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


#pragma once
#include "Hand.h"
#include "dllapi.h"

#define DX_DOWN -1
#define DX_UP	1
#define DY_DOWN -1
#define DY_UP	1
#define DZ_DOWN -1
#define DZ_UP	1


#define VX_DOWN -65
#define VX_UP	65
#define VY_DOWN -65
#define VY_UP	65
#define VZ_DOWN -125
#define VZ_UP	125


#define IS_DATA_BETWEEN(a,d,u)  ((a) >= (d) && (a) <= (u))

//inline bool isDataBetween(int data, int downSide, int upSide)
//{
//	return (data >= downSide && data <= upSide);
//}


typedef struct _GestureArgs
{
	int x;
	int y;
	float z;

	int vx;
	int vy;
	int vz;

	int dx;
	int dy;
	int dz;

	int retainTime;
	bool isRetain;
	bool isSwip;
	bool isMove;

	_GestureArgs()
	{
		reset();
	}
	void reset()
	{
		x = y = 0;
		z = 0.0;
		vx = vy = vz = 0.0;
		dx = dy = dz = 0; 
		retainTime = 0;
		isRetain = false;
		isSwip = false;
		isMove = false;
	}

	inline void setXYZ(int x, int y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline void setDxDyDz(int dx, int dy, int dz, int timeInterval)
	{
		this->dx = dx;
		this->dy = dy;
		this->dz = dz;

		if (IS_DATA_BETWEEN(dx, DX_DOWN, DX_UP)
			&& IS_DATA_BETWEEN(dy, DY_DOWN, DY_UP)
			&& IS_DATA_BETWEEN(dz, DZ_DOWN, DZ_UP))
		{
			retainTime += timeInterval;
			if (retainTime >= 500)
			{
				isRetain = true;
				isMove = false;
			}
		}
		else{
			retainTime = 0;
			isRetain = false;
			isMove = true;
		}
	}

	inline void setVxVyVz(int vx, int vy, int vz)
	{
		this->vx = vx;
		this->vy = vy;
		this->vz = vz;

		if (!IS_DATA_BETWEEN(vx, VX_DOWN, VX_UP)
			|| !IS_DATA_BETWEEN(vy, VY_DOWN, VY_UP)
			|| !IS_DATA_BETWEEN(vz, VZ_DOWN, VZ_UP))
		{
			isSwip = true;
		}
		else{
			isSwip = false;
		}
	}
}GestureArgs;

//手势识别的接口类
class DLL_API GestureEventHandler
{
public:
	GestureEventHandler(){}
	virtual ~GestureEventHandler(){}
	virtual void onOneFingerMove(GestureArgs * args){}
	virtual void onOneFingerTouch(GestureArgs * args){}
	virtual void onHandMove(GestureArgs * args){}
	virtual void onHandPush(GestureArgs * args){}
	virtual void onHandPull(GestureArgs * args){}
	virtual void onHandHoldMove(GestureArgs * args){}
	virtual void onHandHoldPush(GestureArgs * args){}
	virtual void onHandHoldPull(GestureArgs * args){}
	virtual void onHandGrab(GestureArgs * args){}
	virtual void onHandRelease(GestureArgs * args){}
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
	TYPE_UNKNOWN,
	TYPE_GRAB,
	TYPE_RELEASE,
	TYPE_DRAG
};

class DLL_API GestureRecgnition
{
public:
	GestureRecgnition();
	~GestureRecgnition();

	void start(Hand * hand);
	void refresh(Hand * hand);
	void update(Hand * hand);
	void changeState(Hand * hand);

	void tickUp();

	void recgnition();
	GestureType getType();

	void setGestureEventsHandler(GestureEventHandler * handler);
	void setType(GestureType type);
	virtual void onFingerMove(GestureArgs * args){}
	virtual void onFingerTouch(GestureArgs * args){}

	virtual void onGrab(GestureArgs * args){}
	virtual void onRelease(GestureArgs * args){}
	
	virtual void onHandMove(GestureArgs * args){}
	virtual void onHandPush(GestureArgs * args){}
	virtual void onHandPull(GestureArgs * args){}
	
	virtual void onFistMove(GestureArgs * args){}
	virtual void onFistPush(GestureArgs * args){}
	virtual void onFistPull(GestureArgs * args){}
	
private:
	bool isfirstGetGesture;

	GestureType m_type;
	GestureType m_lastType;

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


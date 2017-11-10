#pragma once
#include "Hand.h"


typedef struct _GestureArgs
{
	int x;
	int y;
	int z;

	double vx;
	double vy;
	double vz;
}GestureArgs;

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
	void setType(GestureType type);
private:
	GestureType m_type;
	int startX, startY, startZ;
	int endX, endY, endZ;
	double time;
};


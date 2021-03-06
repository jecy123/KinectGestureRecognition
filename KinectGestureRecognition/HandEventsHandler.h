#pragma once
#include "GestureRecgnition.h"
class HandEventsHandler : public GestureEvents
{
public:
	POINT cursorPoint;

	double maxPositiveVz, maxNagativeVz;
	double minPositiveVz, minNagativeVz;

	HandEventsHandler();
	~HandEventsHandler();
	
	void onOneFingerMove(GestureArgs * args);
	void onOneFingerTouch(GestureArgs * args);
	void onHandMove(GestureArgs * args); 
	void onHandPush(GestureArgs * args); 
	void onHandPull(GestureArgs * args); 
	void onHandHoldMove(GestureArgs * args); 
	void onHandHoldPush(GestureArgs * args); 
	void onHandHoldPull(GestureArgs * args);
	void onHandGrab(GestureArgs * args);
	void onHandRelease(GestureArgs * args);
};


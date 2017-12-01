#define DLL_IMPLEMENT

#include "HandEventsHandler.h"
#include "utils.h"


HandEventsHandler::HandEventsHandler()
{
}


HandEventsHandler::~HandEventsHandler()
{
}

void HandEventsHandler::onOneFingerMove(GestureArgs * args)
{
	gotoXY(0, 20);
	cout << "finger move";
}

void HandEventsHandler::onOneFingerTouch(GestureArgs * args)
{}

void HandEventsHandler::onHandMove(GestureArgs * args)
{}

void HandEventsHandler::onHandPush(GestureArgs * args)
{}

void HandEventsHandler::onHandPull(GestureArgs * args)
{}

void HandEventsHandler::onHandHoldMove(GestureArgs * args)
{}

void HandEventsHandler::onHandHoldPush(GestureArgs * args)
{}

void HandEventsHandler::onHandHoldPull(GestureArgs * args)
{}

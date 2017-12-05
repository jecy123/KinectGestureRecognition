#include "HandEventsHandler.h"
#include "utils.h"


HandEventsHandler::HandEventsHandler()
{
	//maxPositiveVz, maxNagativeVz;
	//minPositiveVz, minNagativeVz;
}


HandEventsHandler::~HandEventsHandler()
{
}

void HandEventsHandler::onOneFingerMove(GestureArgs * args)
{
	gotoXY(0, 20);

	GetCursorPos(&cursorPoint);
	
	cout << cursorPoint.x << "," << cursorPoint.y << endl;
	int x =cursorPoint.x + args->dx * 1366 / 200;
	int y = cursorPoint.y + args->dy * 768 / 200;
	SetCursorPos(x, y);


	cout << "finger move       ";
}

void HandEventsHandler::onOneFingerTouch(GestureArgs * args)
{
	gotoXY(0, 22);
	cout << endl;
	cout << "finger touch     ";
}

void HandEventsHandler::onHandMove(GestureArgs * args)
{

	gotoXY(0, 20);
	cout << endl;
	cout << "hand move        ";
}

void HandEventsHandler::onHandPush(GestureArgs * args)
{

	gotoXY(0, 20);
	cout << endl;
	cout << "hand push           ";
}

void HandEventsHandler::onHandPull(GestureArgs * args)
{

	gotoXY(0, 20);
	cout << endl;
	cout << "hand PULL           ";
}

void HandEventsHandler::onHandHoldMove(GestureArgs * args)
{

	gotoXY(0, 20);
	cout << endl;
	cout << "HandHold Move          ";
}

void HandEventsHandler::onHandHoldPush(GestureArgs * args)
{
	gotoXY(0, 20);
	cout << endl;
	cout << "HandHold Push        ";
}

void HandEventsHandler::onHandHoldPull(GestureArgs * args)
{

	gotoXY(0, 20);
	cout << endl;
	cout << "HandHold Pull        ";
}

void HandEventsHandler::onHandGrab(GestureArgs * args)
{
	gotoXY(0, 22);
	cout << endl;
	cout << "Hand Grab        ";
}

void HandEventsHandler::onHandRelease(GestureArgs * args)
{
	gotoXY(0, 22);
	cout << endl;
	cout << "Hand Release        ";
}

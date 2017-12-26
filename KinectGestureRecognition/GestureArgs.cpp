#include "GestureArgs.h"


GestureArgs::GestureArgs()
{
	this->leftHand = leftHand;
	this->rightHand = rightHand;
}

GestureArgs::~GestureArgs()
{
}


void GestureArgs::reset()
{
	leftHand.reset();
	rightHand.reset();
}

void GestureArgs::setXYZ(int lx, int ly, float lz, int rx, int ry, float rz, unsigned long currentTime)
{
	this->leftHand.setXYZ(lx, ly, lz, currentTime);
	this->rightHand.setXYZ(rx, ry, rz, currentTime);
}

void GestureArgs::setTipXYZ(int lx, int ly, float lz, int rx, int ry, float rz)
{
	this->leftHand.setTipXYZ(lx, ly, lz);
	this->rightHand.setTipXYZ(rx, ry, rz);
}

void GestureArgs::setVxVyVz(int lvx, int lvy, int lvz, int rvx, int rvy, int rvz)
{
	
	this->leftHand.setVxVyVz(lvx, lvy, lvz);
	this->rightHand.setVxVyVz(rvx, rvy, rvz);
}

void GestureArgs::setDxDyDz(int ldx, int ldy, int ldz, int rdx, int rdy, int rdz, int timeInterval)
{
	this->leftHand.setDxDyDz(ldx, ldy, ldz, timeInterval);
	this->rightHand.setDxDyDz(rdx, rdy, rdz, timeInterval);
}


void GestureArgs::calculateCurvity()
{
	this->leftHand.calculateCurvity();
	this->leftHand.calculateCurvity();
}

handStatus GestureArgs::isZoom()
{
	handStatus left = 0;
	handStatus right = 0;
	if (leftHand.isZoom)
	{
		left = STATUS_LEFT;
	}
	if (rightHand.isZoom)
	{
		right = STATUS_RIGHT;
	}
	return left | right;
}

handStatus GestureArgs::isSwip()
{
	handStatus left = 0;
	handStatus right = 0;
	if (leftHand.isSwip)
	{
		left = STATUS_LEFT;
	}
	if (rightHand.isSwip)
	{
		right = STATUS_RIGHT;
	}
	return left | right;
}

handStatus GestureArgs::isMove()
{
	handStatus left = 0;
	handStatus right = 0;
	if (leftHand.isMove)
	{
		left = STATUS_LEFT;
	}
	if (rightHand.isMove)
	{
		right = STATUS_RIGHT;
	}
	return left | right;
}

handStatus GestureArgs::isSwitched()
{
	handStatus left = 0;
	handStatus right = 0;
	if (leftHand.isRetain)
	{
		left = STATUS_LEFT;
	}
	if (rightHand.isRetain)
	{
		right = STATUS_RIGHT;
	}
	return left | right;
}


handStatus GestureArgs::isGrab()
{
	handStatus left = 0;
	handStatus right = 0;
	if (leftHand.isGrab)
	{
		left = STATUS_LEFT;
	}
	if (rightHand.isGrab)
	{
		right = STATUS_RIGHT;
	}
	return left | right;
}

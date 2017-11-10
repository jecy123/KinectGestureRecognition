#pragma once

#include "HandPoint.h"
class Vector
{
public:
	Vector(HandPoint & p1, HandPoint & p2);
	Vector();
	~Vector();

	HandPoint m_ptStart;
	HandPoint m_ptEnd;
};


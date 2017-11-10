#include "GestureRecgnition.h"
#include "utils.h"


GestureRecgnition::GestureRecgnition()
{
}


GestureRecgnition::~GestureRecgnition()
{
}


void GestureRecgnition::start(Hand * hand)
{

}


void GestureRecgnition::recgnition()
{

}


void GestureRecgnition::update(Hand * hand)
{
	string s;
	switch (hand->m_handState)
	{
	case HandState_Open:
		s = "Open      ";
		m_type = TYPE_OPEN;
		break;
	case HandState_Closed:
		s = "Closed    ";
		m_type = TYPE_HOLD;
		break;
	case HandState_Lasso:
		s = "OneFinger ";
		m_type = TYPE_ONE_FINGER;
		break;
	case HandState_NotTracked:
		m_type = TYPE_UNKNOWN;
		s = "NotTracked ";
		break;
	case HandState_Unknown:
		m_type = TYPE_UNKNOWN;
		s = "UnKnown    ";
		break;
	}
	gotoXY(0, 3);
	cout << s;
}

GestureType GestureRecgnition::getType()
{
	return m_type;
}

void GestureRecgnition::setType(GestureType type)
{
	this->m_type = type;
}

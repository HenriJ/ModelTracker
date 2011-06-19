#include "stdafx.h"
#include "Position.h"


Position::Position(void)
{
	x = 0;
	y = 0;
	r = 0;
}

Position::Position(int _x, int _y, double _r)
{
	x = _x;
	y = _y;
	r = _r;
}

Position(Point p, double _r)
{
	x = p.x;
	y = p.y;
	r = _r;
}

Position::~Position(void)
{
}

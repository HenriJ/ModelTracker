#pragma once
#include "stdafx.h"

class Position
{
public:
	Position(void);
	Position(int x, int y, double r);
	Position(Point p, double r);
	virtual ~Position(void);

	int x;
	int y;
	double r;
};


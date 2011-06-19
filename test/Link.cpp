#include "stdafx.h"
#include "Position.h"
#include "Link.h"


Link::Link(void)
{
}


Link::~Link(void)
{
}

int Link::first_member()
{
	return first_member_;
}

int Link::second_member()
{
	return second_member_;
}

double Link::energy(Position& pa, Position& pb)
{
	return 0;
}
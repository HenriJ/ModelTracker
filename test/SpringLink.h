#pragma once
#include "link.h"

class SpringLink :
	public Link
{
public:
	SpringLink(double _l0, double _k);
	virtual ~SpringLink(void);
	double energy(Position pa, Position pb);

private:
	double l0_;
	double k_;
};


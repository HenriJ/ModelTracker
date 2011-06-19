#include "stdafx.h"
#include "Position.h"
#include "Arrangement.h"

using namespace std;


Arrangement::Arrangement(void)
{
}

Arrangement::Arrangement(string filename)
{
	// TODO
}

Arrangement::~Arrangement(void)
{
}

Position& Arrangement::operator[] (unsigned int i)
{
	return positions_[i];
}

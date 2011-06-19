#pragma once
#include "stdafx.h"
#include "Position.h"

class Arrangement
{
public:
	Arrangement(void);
	Arrangement(std::string filename);
	virtual ~Arrangement(void);
	Position& operator[] (unsigned int i);

private:
	std::vector<Position> positions_;
};


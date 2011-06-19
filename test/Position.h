#pragma once
class Position
{
public:
	Position(void);
	Position(int x, int y, double r);
	virtual ~Position(void);

	int x;
	int y;
	double r;
};


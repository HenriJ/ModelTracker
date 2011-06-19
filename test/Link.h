#pragma once
class Link
{
public:
	Link(void);
	virtual ~Link(void);
	int first_member();
	int second_member();
	double energy(Position& pa, Position& pb);

private:
	int first_member_;
	int second_member_;
};


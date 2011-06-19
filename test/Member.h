#pragma once
#include "stdafx.h"
#include "Position.h"

class Member
{
public:
	Member();
	~Member(void);
	virtual double energy(cv::Mat& haystack, Position& p) = 0;
	virtual std::map<double, cv::Mat> energyField(cv::Mat& haystack) = 0;
	virtual Position bestPosition(cv::Mat& haystack) = 0;
	virtual std::map<double, Position> bestPositions(cv::Mat& haystack, unsigned int n_best) = 0;

private:
	std::vector<cv::Mat> probs;
};


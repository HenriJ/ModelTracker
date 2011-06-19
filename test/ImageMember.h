#pragma once
#include "stdafx.h"
#include "Position.h"
#include "Member.h"

class ImageMember :
	public Member
{
public:
	ImageMember(std::string path, std::vector<std::string>& args);
	virtual ~ImageMember(void);
	double energy(cv::Mat& haystack, Position& p);
	std::map<double, cv::Mat> energyField(cv::Mat& haystack);
	Position bestPosition(cv::Mat& haystack);

private:
	cv::Mat image;
	double delta_theta_;
	std::map<double, cv::Mat> rotation_cache_;

	cv::Mat rotateMat(cv::Mat& m, double angle);
	cv::Mat& getRotatedImage(double angle);
};

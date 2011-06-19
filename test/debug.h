#pragma once
#include "stdafx.h"
#include "Position.h"

void onMouse(int event, int x, int y, int flags, void* image);

void tic();
void toc();

void trace(unsigned int i);
void trace(double d);
void trace(std::string s);
void trace(Position p);
void trace(std::vector<std::string>& vs);
void trace(cv::Mat& m, bool hdr = true);
void trace(std::vector<cv::Mat>& v);
void trace(std::map<double, cv::Mat>& field);

void pause();
void pause(unsigned int i);
void pause(double d);
void pause(std::string s);
void pause(Position p);
void pause(cv::Mat& m, bool hdr = true);
void pause(std::vector<cv::Mat>& v);
void pause(std::vector<std::string>& vs);
void pause(std::map<double, cv::Mat>& field);
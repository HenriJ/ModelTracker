#include "stdafx.h"
#include "debug.h"
#include "Member.h"
#include "ImageMember.h"
#include "Arrangement.h"
#include <math.h>
#include "Model.h"

#define PI 3.14159265

using namespace std;
using namespace cv;

void bgrToGray(Mat& m) {
	Mat temp;
	cvtColor(m, temp, CV_BGR2GRAY);
	m = temp;
}

void arrow(Mat& img, Point& p1, Point& p2)
{
	line(img, p1, p2, 255);
	circle(img, p2, 10, 255);
}

void arrow(Mat& img, Position p, double l)
{
	Point p1(p.x, p.y);
	Point p2(p.x + l * sin(p.r * PI / 180), p.y - l * cos(p.r * PI / 180));

	arrow(img, p1, p2);
}

int main(int argc, const char* argv[])
{
	Mat haystack = imread("zflc.png", 0);

	Model zfl("model/zfl.txt");

	Mat disp = haystack.clone();

	Member& m = zfl.getMember("taila1");

	Position p = m.bestPosition(haystack);

	trace(p);

	arrow(disp, p, 40);

	pause(disp);

	pause(zfl.members());

	pause();

    return 0;
}

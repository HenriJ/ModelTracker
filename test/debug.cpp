#include "stdafx.h"
#include "debug.h"

using namespace cv;
using namespace std;

double debug_tic_toc = 0;

void tic()
{
	debug_tic_toc = (double) getTickCount();
}

void toc()
{
	cout << "Toc " << ((double)getTickCount() - debug_tic_toc)/getTickFrequency() << endl;
}

void onMouse(int event, int x, int y, int flags, void* image)
{
	if (event == 0) {
		cout << '\xd' << "                                            " << '\xd';
		cout << "Mouse x:" << x << "; y:" << y << " => ";
		Mat* m = (Mat*) image;
		try {
			if (m->type() == DataType<unsigned char>::type) {
				cout << " (uchar) " << (int) m->at<unsigned char>(y, x);
			} else if (m->type() == DataType<double>::type) {
				cout << " (double) " << m->at<double>(y, x);
			} else {
			    cout << " (float) " << m->at<float>(y, x);
			}
		} catch(...) {
			cout << "Erreur";
		}
	}
	if (event == 1) {
		cout << endl;
	}
}

void trace(unsigned int i)
{
	cout << "Trace unsigned int" << endl;
	cout << i << endl;
}

void trace(double d)
{
	cout << "Trace double" << endl;
	cout << d << endl;
}

void trace(std::string s)
{
	cout << "Trace std::string size = " << s.size() << endl;
	cout << s << endl;
}

void trace(Position p)
{
	cout << "Trace Position" << endl;
	cout << "x: " << p.x << " y: " << p.y << " r: " << p.r << endl;
}

void trace(std::vector<std::string>& vs)
{
	cout << "Trace std::vector<std::string> size = " << vs.size() << endl;
	for (unsigned int i = 0; i < vs.size(); ++i) {
		cout << i << " : " << vs[i] << endl;
	}
}

void trace(Mat& m, bool hdr)
{
	cout << endl << "Trace " << m.cols << " x " << m.rows << " : " << m.type();

	if (m.channels() > 1) {
		hdr = false;
	}

	string win = "trace";
	namedWindow(win, CV_GUI_EXPANDED);
	if (hdr) {
		double minVal, maxVal;
		minMaxLoc(m, &minVal, &maxVal);

		cout << " min: " << minVal << " max: " << maxVal;

		Mat copy;
		m.convertTo(copy, DataType<float>::type, 1./(maxVal-minVal), -minVal);

		imshow(win, copy);
	} else {
		imshow(win, m);
	}

	cout << endl;
	setMouseCallback(win, onMouse, (void*) (&m));
}

void trace(vector<Mat>& v)
{
	for (unsigned i = 0; i < v.size(); ++i) {
		trace(v[i]);
	}
}

void trace(map<double, Mat>& field)
{
	vector<Mat> mats(field.size());
	int i = 0;
	for (map<double, Mat>::iterator it = field.begin(); it != field.end(); ++it) {
		mats[i] = it->second;
		++i;
	}

	pause(mats);
}

void pause()
{
	cout << "Pause" << endl;
	string t;
	cin >> t;
}

void pause(unsigned int i)
{
	trace(i);
	pause();
}

void pause(double d)
{
	trace(d);
	pause();
}

void pause(string s)
{
	trace(s);
	pause();
}

void pause(Position p)
{
	trace(p);
	pause();
}

void pause(Mat& m, bool hdr)
{
	trace(m);
	waitKey(0);
}

void pause(std::vector<cv::Mat>& v)
{
	for (unsigned i = 0; i < v.size(); ++i) {
		pause(v[i]);
	}
}

void pause(vector<string>& vs)
{
	trace(vs);
	pause();
}

void pause(map<double, Mat>& field)
{
	trace(field);
	waitKey(0);
}
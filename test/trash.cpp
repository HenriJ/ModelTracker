

DWORD WINAPI mouseThread( void* lpParam ) 
{
	setMouseCallback("Test", onMouse, lpParam);

	while (((Point*)lpParam)->x == -1) {
		Sleep(10);
	}

	return 0;
}

void onMouse(int event, int x, int y, int flags, void* ret) {
	if (event == 1) {
		((Point*)ret)->x = x;
		((Point*)ret)->y = y;
	}
}

Point waitMouse(const char* win) {
	DWORD threadID;

	Point* pos = new Point(-1, -1);

	CreateThread( 
        NULL,                   // default security attributes
        0,                      // use default stack size  
        mouseThread,            // thread function name
        (void*) pos,            // argument to thread function 
        0,                      // use default creation flags 
        &threadID);				// returns the thread identifier

	while(((Point*)pos)->x == -1) {
		Sleep(10);
	}

	return *pos;
}

	/*VideoCapture video;
	video.open("B.avi");

	Mat frame;
	video.grab();
	video.retrieve(frame);
	bgrToGray(frame);*/

	Model zfl("model/zfl.txt");


	//Mat featureMat = imread("head.png", 0);
	//Feature head(featureMat, 16);
	//frame = imread("zfl.png", 0);
	//head.compute(frame);
	//Point p;
	//double angle = 666;
	//head.bestGuess(p, angle);
	//cout << "angle" << angle << endl;
	//arrow(frame, p, p - Point(featureMat.cols/2 * sin(angle * PI / 180), featureMat.rows/2 * cos(angle * PI / 180)));
	//trace(frame);

	//unsigned f = 0;
	//while (video.grab()) {
	//	++f;
	//	cout << f << endl;

	//	video.retrieve(frame);
	//	bgrToGray(frame);
	//}

	void Member::compute(Mat& m)
{
	for (unsigned i = 0; i < features.size(); ++i) {
		Mat prob;

		matchTemplate(m, features[i], probs[i], CV_TM_CCOEFF_NORMED);
	}
}
void Member::bestGuess(Point& bestP, double& angle)
{
	double bestProb = 0;
	int bestI = 0;

	for (unsigned i = 0; i < features.size(); ++i) {
		double minVal, maxVal;
		Point maxLoc;
		minMaxLoc(probs[i], &minVal, &maxVal, NULL, &maxLoc);

		if (maxVal > bestProb) {
			bestProb = maxVal;
			bestP = Point(maxLoc.x + features[i].cols/2, maxLoc.y + features[i].rows/2);
			bestI = i;
		}
	}

	double delta = 360. / rot;
	angle = bestI * delta;
}
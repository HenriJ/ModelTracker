#include "stdafx.h"
#include "debug.h"

#include "ImageMember.h"

using namespace std;
using namespace cv;

// args: head.png
ImageMember::ImageMember(const string path, vector<string>& args)
{
	string filename = args[0];
	delta_theta_ = atof(args[1].c_str());

	image = imread(path + "/" + filename, 0);

	buildCache();
}

ImageMember::~ImageMember(void)
{
}

void ImageMember::buildCache()
{
	for (double theta = 0; theta < 360; theta += delta_theta_) {
		getRotatedImage(theta);
	}
}

double ImageMember::energy(Mat& haystack, Position& p)
{
	Mat& feature = getRotatedImage(p.r);

	Rect roi(p.x - feature.cols, p.y - feature.rows, 2 * feature.cols, 2 * feature.rows);

	Mat result;
	matchTemplate(haystack(roi), feature, result, CV_TM_CCOEFF_NORMED);

	return result.at<float>(feature.rows, feature.cols);
}

map<double, Mat> ImageMember::energyField(cv::Mat& haystack)
{
	map<double, Mat> energy_field;

	for (double theta = 0; theta < 360; theta += delta_theta_) {
		tic();
		matchTemplate(haystack, getRotatedImage(theta), energy_field[theta], CV_TM_CCOEFF_NORMED);
		toc();
	}

	return energy_field;
}

Position ImageMember::bestPosition(Mat& haystack)
{
	map<double, Mat>& energy_field = energyField(haystack);

	double bestProb = 0;
	Point bestPoint;
	double bestTheta = 0;

	for (map<double, Mat>::iterator it = energy_field.begin(); it != energy_field.end(); ++it) {
		Mat& feature = rotation_cache_[it->first];

		double minVal, maxVal;
		Point maxLoc;
		minMaxLoc(it->second, &minVal, &maxVal, NULL, &maxLoc);

		if (maxVal > bestProb) {
			bestProb = maxVal;
			bestPoint = Point(maxLoc.x + feature.cols/2, maxLoc.y + feature.rows/2);
			bestTheta = it->first;
		}
	}

	return Position(bestPoint.x, bestPoint.y, bestTheta);
}

map<double, Position> ImageMember::bestPositions(Mat& haystack, int n_best)
{
	// TODO use heap with push_heap
	// don't forget we are rtying to minimize the energy

	map<double, Position> best_positions;

	map<double, Mat> energy_field = energyField(haystack);

	for (map<double, Mat>::iterator it = energy_field.begin(); it != energy_field.end(); ++it) {
		map<double, Point> local_best_positions;

		Mat& energy = it->second;
		Mat& feature = rotation_cache_[it->first];

		MatIterator_<float> mit = energy.begin<float>();
		MatIterator_<float> mit_end = energy.end<float>();
		for(; mit != mit_end; ++it) {
			local_best_positions[(double) *mit] = mit.pos();
		}
		
		map<double, Point>::iterator lit = local_best_positions.end();
		map<double, Point>::iterator lit_begin = local_best_positions.begin();
		int n = 0;
		for(; lit != lit_begin && n < n_best; --lit, ++n) {
			best_positions[lit->first] = Position(lit->second, it->first);
		}
	}

	return best_positions;
}

Mat& ImageMember::getRotatedImage(double angle)
{
	if(rotation_cache_.find(angle) == rotation_cache_.end()) {
		rotation_cache_[angle] = rotateMat(image, angle);
	}

	return rotation_cache_[angle];
}

Mat ImageMember::rotateMat(Mat& m, double angle)
{
	if (angle == 0) {
		return m;
	}

    Point2f src_center(m.cols/2.0F, m.rows/2.0F);
    Mat rot_mat = getRotationMatrix2D(src_center, angle, 1.0);

	Size oldSize = m.size();
	Size newSize((int) (oldSize.width * 1.5), (int) (oldSize.height * 1.5));

	rot_mat.at<double>(0, 2) += (newSize.width - oldSize.width)/2.0F;
	rot_mat.at<double>(1, 2) += (newSize.height - oldSize.height)/2.0F;
    Mat dst;

    warpAffine(m, dst, rot_mat, newSize, INTER_LINEAR, BORDER_CONSTANT, 255);
    return dst;
}
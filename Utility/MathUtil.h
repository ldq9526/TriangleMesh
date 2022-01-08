#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include <opencv2/opencv.hpp>

class MathUtil
{
public:
	const static double EPS;
	const static double PI;

public:
	static bool isZero(double v);
	static bool isZero(const cv::Vec3d& v);
};

#endif
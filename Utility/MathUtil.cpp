#include "MathUtil.h"

const double MathUtil::EPS = 1e-6;
const double MathUtil::PI = 3.1415926535;

bool MathUtil::isZero(double v)
{
	return cv::abs(v) < EPS;
}


bool MathUtil::isZero(const cv::Vec3d& v)
{
	return cv::norm(v, cv::NORM_L2) < EPS;
}
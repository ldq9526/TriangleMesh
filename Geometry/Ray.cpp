#include "Ray.h"
#include "Utility/MathUtil.h"

Ray::Ray()
{
	o = cv::Vec3d(0.0, 0.0, 0.0);
	d = cv::Vec3d(0.0, 0.0, 0.0);
}

Ray::Ray(const cv::Vec3d& o, const cv::Vec3d& d)
{
	this->o = o;

	if (MathUtil::isZero(d))
	{
		this->d = cv::Vec3d(0.0, 0.0, 0.0);
	}
	else
	{
		this->d = cv::normalize(d);
	}
}

cv::Vec3d Ray::getPoint(double t) const
{
	return o + t * d;
}

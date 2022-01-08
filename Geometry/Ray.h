#ifndef RAY_H
#define RAY_H

#include <opencv2/opencv.hpp>

class Ray
{
public:
	/// <summary>
	/// 射线起点
	/// </summary>
	cv::Vec3d o;

	/// <summary>
	/// 射线方向, 单位向量
	/// </summary>
	cv::Vec3d d;

public:
	Ray();
	Ray(const cv::Vec3d& o, const cv::Vec3d& d);

	/// <summary>
	/// 返回t参数代表的点
	/// </summary>
	/// <param name="t"></param>
	/// <returns></returns>
	cv::Vec3d getPoint(double t) const;
};

#endif
#ifndef AABB_H
#define AABB_H

#include "Ray.h"

#include <opencv2/opencv.hpp>

class AABB
{
public:
	cv::Vec3d minPoint;
	cv::Vec3d maxPoint;

protected:
	/// <summary>
	/// 是否包含某点
	/// </summary>
	/// <param name="point"></param>
	/// <returns></returns>
	bool enclosesPoint(const cv::Vec3d& point) const;

public:
	AABB();

	/// <summary>
	/// 重置包围盒
	/// </summary>
	void reset();

	/// <summary>
	/// 合并AABB
	/// </summary>
	/// <param name="aabb"></param>
	void merge(const AABB& aabb);

	/// <summary>
	/// 包围盒与射线相交
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	bool intersectsRay(const Ray& ray) const;

	/// <summary>
	/// 获取沿x轴的长度
	/// </summary>
	/// <returns></returns>
	double lengthX() const;

	/// <summary>
	/// 获取沿y轴的长度
	/// </summary>
	/// <returns></returns>
	double lengthY() const;

	/// <summary>
	/// 获取沿z轴的长度
	/// </summary>
	/// <returns></returns>
	double lengthZ() const;

	/// <summary>
	/// 获取包围盒中心点
	/// </summary>
	/// <returns></returns>
	cv::Vec3d center() const;
};

#endif
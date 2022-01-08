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
	/// �Ƿ����ĳ��
	/// </summary>
	/// <param name="point"></param>
	/// <returns></returns>
	bool enclosesPoint(const cv::Vec3d& point) const;

public:
	AABB();

	/// <summary>
	/// ���ð�Χ��
	/// </summary>
	void reset();

	/// <summary>
	/// �ϲ�AABB
	/// </summary>
	/// <param name="aabb"></param>
	void merge(const AABB& aabb);

	/// <summary>
	/// ��Χ���������ཻ
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	bool intersectsRay(const Ray& ray) const;

	/// <summary>
	/// ��ȡ��x��ĳ���
	/// </summary>
	/// <returns></returns>
	double lengthX() const;

	/// <summary>
	/// ��ȡ��y��ĳ���
	/// </summary>
	/// <returns></returns>
	double lengthY() const;

	/// <summary>
	/// ��ȡ��z��ĳ���
	/// </summary>
	/// <returns></returns>
	double lengthZ() const;

	/// <summary>
	/// ��ȡ��Χ�����ĵ�
	/// </summary>
	/// <returns></returns>
	cv::Vec3d center() const;
};

#endif
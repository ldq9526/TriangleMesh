#ifndef RAY_H
#define RAY_H

#include <opencv2/opencv.hpp>

class Ray
{
public:
	/// <summary>
	/// �������
	/// </summary>
	cv::Vec3d o;

	/// <summary>
	/// ���߷���, ��λ����
	/// </summary>
	cv::Vec3d d;

public:
	Ray();
	Ray(const cv::Vec3d& o, const cv::Vec3d& d);

	/// <summary>
	/// ����t��������ĵ�
	/// </summary>
	/// <param name="t"></param>
	/// <returns></returns>
	cv::Vec3d getPoint(double t) const;
};

#endif
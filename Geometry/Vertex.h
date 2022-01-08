#ifndef VERTEX_H
#define VERTEX_H

#include <opencv2/opencv.hpp>

class Vertex
{
public:
	/// <summary>
	/// 顶点坐标
	/// </summary>
	cv::Vec3d position;

	/// <summary>
	/// 顶点法向量
	/// </summary>
	cv::Vec3d normal;

public:
	Vertex();

	Vertex(const cv::Vec3d& position, const cv::Vec3d& normal);
};

#endif
#ifndef INTERSECTION_INFO_H
#define INTERSECTION_INFO_H

#include "Ray.h"
#include "Vertex.h"

struct IntersectionInfo
{
	/// <summary>
	/// 与几何体相交的射线
	/// </summary>
	Ray ray;

	/// <summary>
	/// 射线的参数
	/// </summary>
	double t;

	/// <summary>
	/// 交点的顶点信息
	/// </summary>
	Vertex vertex;

	IntersectionInfo();
};

#endif
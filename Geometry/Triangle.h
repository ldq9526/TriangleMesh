#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include "Vertex.h"

class Triangle: public Shape
{
protected:
	const Vertex* vertices[3];

	/// <summary>
	/// 三角形所在平面的法向量
	/// </summary>
	cv::Vec3d normal;

	void computeAABB() override;

	/// <summary>
	/// 射线是否从三角形所在平面射出
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	bool startsRay(const Ray& ray) const;

public:
	Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);

	bool intersectsRay(const Ray& ray) const override;

	bool intersectsRay(const Ray& ray, IntersectionInfo* info) const override;
};

#endif
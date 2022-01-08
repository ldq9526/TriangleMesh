#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include "Vertex.h"

class Triangle: public Shape
{
protected:
	const Vertex* vertices[3];

	/// <summary>
	/// ����������ƽ��ķ�����
	/// </summary>
	cv::Vec3d normal;

	void computeAABB() override;

	/// <summary>
	/// �����Ƿ������������ƽ�����
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
#ifndef SHAPE_H
#define SHAPE_H

#include "AABB.h"
#include "Ray.h"
#include "Vertex.h"
#include "IntersectionInfo.h"

class Shape
{
public:
	/// <summary>
	/// ������Χ��
	/// </summary>
	AABB aabb;

protected:
	/// <summary>
	/// ����AABB
	/// </summary>
	virtual void computeAABB() = 0;

public:
	/// <summary>
	/// �����Ƿ��뼸�����ཻ
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	virtual bool intersectsRay(const Ray& ray) const = 0;

	/// <summary>
	/// �����Ƿ��뼸�����ཻ
	/// </summary>
	/// <param name="ray">����</param>
	/// <param name="info">�ཻ��Ϣ</param>
	/// <returns></returns>
	virtual bool intersectsRay(const Ray& ray, IntersectionInfo* info) const = 0;
};

#endif
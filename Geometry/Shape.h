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
	/// 轴对齐包围盒
	/// </summary>
	AABB aabb;

protected:
	/// <summary>
	/// 计算AABB
	/// </summary>
	virtual void computeAABB() = 0;

public:
	/// <summary>
	/// 射线是否与几何体相交
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	virtual bool intersectsRay(const Ray& ray) const = 0;

	/// <summary>
	/// 射线是否与几何体相交
	/// </summary>
	/// <param name="ray">射线</param>
	/// <param name="info">相交信息</param>
	/// <returns></returns>
	virtual bool intersectsRay(const Ray& ray, IntersectionInfo* info) const = 0;
};

#endif
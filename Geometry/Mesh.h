#ifndef MESH_H
#define MESH_H

#include "Vertex.h"
#include "Triangle.h"
#include "BVHNode.h"

class Mesh: public Shape
{
protected:
	/// <summary>
	/// 顶点集合
	/// </summary>
	std::vector<Vertex> vertices;

	/// <summary>
	/// 三角形
	/// </summary>
	std::vector<Triangle> triangles;

	/// <summary>
	/// BVH根节点
	/// </summary>
	BVHNode* rootBVH;

	/// <summary>
	/// BVH节点集合
	/// </summary>
	std::vector<BVHNode*> nodeCollecter;

protected:
	void computeAABB() override;

public:
	Mesh(const std::vector<cv::Vec3d>& positions, const std::vector<cv::Vec3d>& normals, const std::vector<cv::Vec3i> indices);

	virtual ~Mesh();

	bool intersectsRay(const Ray& ray) const override;

	bool intersectsRay(const Ray& ray, IntersectionInfo* info) const override;
};

#endif
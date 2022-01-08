#ifndef BVH_NODE_H
#define BVH_NODE_H

#include "Triangle.h"

#include <vector>

class BVHNode: public Shape
{
public:
	/// <summary>
	/// node[0]: 分布在分割平面左侧的三角形
	/// node[1]: 分布在分割平面右侧的三角形
	/// node[2]: 横跨分割平面的三角形
	/// </summary>
	BVHNode* node[3];

protected:
	/// <summary>
	/// 每个叶子节点三角形数量的最大值
	/// </summary>
	const static int MAX_TRIANGLES_COUNT;

	/// <summary>
	/// 三角形数组的指针
	/// </summary>
	const std::vector<Triangle>* triangles;

	/// <summary>
	/// 该节点包含的三角形索引
	/// </summary>
	std::vector<int> triangleIndices;

	/// <summary>
	/// 动态分配节点的集合
	/// </summary>
	std::vector<BVHNode*>* nodeCollecter;

protected:
	/// <summary>
	/// 计算AABB
	/// </summary>
	void computeAABB() override;

	/// <summary>
	/// 是否为有效分割
	/// </summary>
	/// <param name="nodeTriangleIndices"></param>
	/// <returns></returns>
	bool isValidSplit(const std::vector<int> nodeTriangleIndices[3]) const;

public:
	BVHNode(const std::vector<Triangle>& triangles, const std::vector<int>& triangleIndices, std::vector<BVHNode*>& collecter);

	/// <summary>
	/// 是否为叶节点
	/// </summary>
	/// <returns></returns>
	bool isLeaf() const;

	/// <summary>
	/// 射线是否与几何体相交, 不需要相交信息
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	bool intersectsRay(const Ray& ray) const override;

	/// <summary>
	/// 射线是否与几何体相交
	/// </summary>
	/// <param name="ray">射线</param>
	/// <param name="info">相交信息</param>
	/// <returns></returns>
	bool intersectsRay(const Ray& ray, IntersectionInfo* info) const override;

	/// <summary>
	/// 开始构建BVH
	/// </summary>
	void createBVH();

	/// <summary>
	/// 三角形数量
	/// </summary>
	/// <returns></returns>
	size_t trianglesCount() const;
};

#endif
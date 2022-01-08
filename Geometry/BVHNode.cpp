#include "BVHNode.h"

const int BVHNode::MAX_TRIANGLES_COUNT = 100;

void BVHNode::computeAABB()
{
	aabb.reset();
	for (size_t i = 0; i < triangleIndices.size(); i++)
	{
		int index = triangleIndices[i];
		aabb.merge((*triangles)[index].aabb);
	}
}

bool BVHNode::isValidSplit(const std::vector<int> nodeTriangleIndices[3]) const
{
	size_t n0 = nodeTriangleIndices[0].size();
	size_t n1 = nodeTriangleIndices[1].size();
	size_t n2 = nodeTriangleIndices[2].size();

	return (n0 > 0 && n1 > 0) || (n0 > 0 && n2 > 0) || (n1 > 0 && n2 > 0);
}

BVHNode::BVHNode(const std::vector<Triangle>& triangles, const std::vector<int>& triangleIndices, std::vector<BVHNode*>& collecter)
{
	this->triangles = &triangles;
	this->triangleIndices = std::vector<int>(triangleIndices);
	this->nodeCollecter = &collecter;
	node[0] = nullptr;
	node[1] = nullptr;
	node[2] = nullptr;

	computeAABB();
}

bool BVHNode::isLeaf() const
{
	return node[0] == nullptr || node[1] == nullptr || node[2] == nullptr;
}

bool BVHNode::intersectsRay(const Ray& ray) const
{
	if (!aabb.intersectsRay(ray))
		return false;

	// 本身为叶子节点: 计算射线与节点内每个三角形的交点
	if (isLeaf())
	{
		for (size_t i = 0; i < triangleIndices.size(); i++)
		{
			if ((*triangles)[triangleIndices[i]].intersectsRay(ray))
				return true;
		}
		return false;
	}
	
	for (int i = 0; i < 3; i++)
	{
		if (node[i]->intersectsRay(ray))
			return true;
	}

	return false;
}

bool BVHNode::intersectsRay(const Ray& ray, IntersectionInfo* info) const
{
	if (info == nullptr)
		return intersectsRay(ray);

	if (!aabb.intersectsRay(ray))
		return false;

	// 本身为叶子节点: 计算射线与节点内每个三角形的交点
	if (isLeaf())
	{
		bool intersected = false;
		for (size_t i = 0; i < triangleIndices.size(); i++)
		{
			IntersectionInfo tempInfo;
			if ((*triangles)[triangleIndices[i]].intersectsRay(ray, &tempInfo))
			{
				if (!intersected || tempInfo.t < info->t)
				{
					info->ray = ray;
					info->t = tempInfo.t;
					info->vertex = tempInfo.vertex;

					if(!intersected)
						intersected = true;
				}
			}
		}
		return intersected;
	}
	
	std::vector<IntersectionInfo> intersectionInfos;
	for (int i = 0; i < 3; i++)
	{
		IntersectionInfo tempInfo;
		if (node[i]->intersectsRay(ray, &tempInfo))
			intersectionInfos.push_back(tempInfo);
	}

	if (intersectionInfos.empty())
		return false;

	size_t index = 0;
	double tmin = intersectionInfos[0].t;
	for (size_t i = 0; i < intersectionInfos.size(); i++)
	{
		if (intersectionInfos[i].t < tmin)
		{
			tmin = intersectionInfos[i].t;
			index = i;
		}
	}

	info->ray = ray;
	info->t = tmin;
	info->vertex = intersectionInfos[index].vertex;

	return true;
}

void BVHNode::createBVH()
{
	if (node[0] != nullptr || node[1] != nullptr || node[2] != nullptr)
		return;

	if (triangleIndices.size() <= MAX_TRIANGLES_COUNT)
		return;

	cv::Vec3d center = aabb.center();

	double bounds[3] = { aabb.lengthX(),aabb.lengthY(),aabb.lengthZ() };
	double* axisPointer = std::max_element(bounds, bounds + 3);
	int axisIndex = int(axisPointer - bounds);

	std::vector<int> nodeTriangleIndices[3];
	for (int dAxis = 0; dAxis < 3; dAxis++)
	{
		int axis = (axisIndex + dAxis) % 3;
		nodeTriangleIndices[0].clear();
		nodeTriangleIndices[1].clear();
		nodeTriangleIndices[2].clear();

		for (size_t i = 0; i < triangleIndices.size(); i++)
		{
			int index = triangleIndices[i];
			if ((*triangles)[index].aabb.maxPoint[axis] < center[axis])
				nodeTriangleIndices[0].push_back(index);
			else if ((*triangles)[index].aabb.minPoint[axis] > center[axis])
				nodeTriangleIndices[1].push_back(index);
			else
				nodeTriangleIndices[2].push_back(index);
		}

		if (isValidSplit(nodeTriangleIndices))
			break;
	}

	if (!isValidSplit(nodeTriangleIndices))
		return;

	for (int i = 0; i < 3; i++)
	{
		node[i] = new BVHNode(*triangles, nodeTriangleIndices[i], *nodeCollecter);
		nodeCollecter->push_back(node[i]);
		node[i]->createBVH();
	}
}

size_t BVHNode::trianglesCount() const
{
	return triangleIndices.size();
}

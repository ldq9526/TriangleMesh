#ifndef BVH_NODE_H
#define BVH_NODE_H

#include "Triangle.h"

#include <vector>

class BVHNode: public Shape
{
public:
	/// <summary>
	/// node[0]: �ֲ��ڷָ�ƽ������������
	/// node[1]: �ֲ��ڷָ�ƽ���Ҳ��������
	/// node[2]: ���ָ�ƽ���������
	/// </summary>
	BVHNode* node[3];

protected:
	/// <summary>
	/// ÿ��Ҷ�ӽڵ����������������ֵ
	/// </summary>
	const static int MAX_TRIANGLES_COUNT;

	/// <summary>
	/// �����������ָ��
	/// </summary>
	const std::vector<Triangle>* triangles;

	/// <summary>
	/// �ýڵ����������������
	/// </summary>
	std::vector<int> triangleIndices;

	/// <summary>
	/// ��̬����ڵ�ļ���
	/// </summary>
	std::vector<BVHNode*>* nodeCollecter;

protected:
	/// <summary>
	/// ����AABB
	/// </summary>
	void computeAABB() override;

	/// <summary>
	/// �Ƿ�Ϊ��Ч�ָ�
	/// </summary>
	/// <param name="nodeTriangleIndices"></param>
	/// <returns></returns>
	bool isValidSplit(const std::vector<int> nodeTriangleIndices[3]) const;

public:
	BVHNode(const std::vector<Triangle>& triangles, const std::vector<int>& triangleIndices, std::vector<BVHNode*>& collecter);

	/// <summary>
	/// �Ƿ�ΪҶ�ڵ�
	/// </summary>
	/// <returns></returns>
	bool isLeaf() const;

	/// <summary>
	/// �����Ƿ��뼸�����ཻ, ����Ҫ�ཻ��Ϣ
	/// </summary>
	/// <param name="ray"></param>
	/// <returns></returns>
	bool intersectsRay(const Ray& ray) const override;

	/// <summary>
	/// �����Ƿ��뼸�����ཻ
	/// </summary>
	/// <param name="ray">����</param>
	/// <param name="info">�ཻ��Ϣ</param>
	/// <returns></returns>
	bool intersectsRay(const Ray& ray, IntersectionInfo* info) const override;

	/// <summary>
	/// ��ʼ����BVH
	/// </summary>
	void createBVH();

	/// <summary>
	/// ����������
	/// </summary>
	/// <returns></returns>
	size_t trianglesCount() const;
};

#endif
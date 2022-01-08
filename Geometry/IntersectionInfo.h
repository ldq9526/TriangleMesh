#ifndef INTERSECTION_INFO_H
#define INTERSECTION_INFO_H

#include "Ray.h"
#include "Vertex.h"

struct IntersectionInfo
{
	/// <summary>
	/// �뼸�����ཻ������
	/// </summary>
	Ray ray;

	/// <summary>
	/// ���ߵĲ���
	/// </summary>
	double t;

	/// <summary>
	/// ����Ķ�����Ϣ
	/// </summary>
	Vertex vertex;

	IntersectionInfo();
};

#endif
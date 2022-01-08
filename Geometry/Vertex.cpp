#include "Vertex.h"
#include "Utility/MathUtil.h"

Vertex::Vertex()
{
	this->position = cv::Vec3d(0.0, 0.0, 0.0);
	this->normal = cv::Vec3d(0.0, 0.0, 0.0);
}

Vertex::Vertex(const cv::Vec3d& position, const cv::Vec3d& normal)
{
	this->position = cv::Vec3d(position);

	if (MathUtil::isZero(normal))
	{
		this->normal = cv::Vec3d(0.0, 0.0, 0.0);
	}
	else
	{
		this->normal = cv::normalize(normal);
	}
}

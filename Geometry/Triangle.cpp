#include "Triangle.h"
#include "Utility/MathUtil.h"

bool Triangle::startsRay(const Ray& ray) const
{
    return
        MathUtil::isZero(normal.dot(vertices[0]->position - ray.o)) ||
        MathUtil::isZero(normal.dot(vertices[1]->position - ray.o)) ||
        MathUtil::isZero(normal.dot(vertices[2]->position - ray.o));
}

Triangle::Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
    vertices[0] = &v0;
    vertices[1] = &v1;
    vertices[2] = &v2;

    normal = (v1.position - v0.position).cross(v2.position - v0.position);

    computeAABB();
}

bool Triangle::intersectsRay(const Ray& ray) const
{
    if (startsRay(ray))
        return false;

    if (!aabb.intersectsRay(ray))
        return false;

    cv::Mat A = (cv::Mat_<double>(4, 4) <<
        vertices[0]->position[0], vertices[1]->position[0], vertices[2]->position[0], -ray.d[0],
        vertices[0]->position[1], vertices[1]->position[1], vertices[2]->position[1], -ray.d[1],
        vertices[0]->position[2], vertices[1]->position[2], vertices[2]->position[2], -ray.d[2],
        1.0, 1.0, 1.0, 0.0);

    cv::Mat b = (cv::Mat_<double>(4, 1) << ray.o[0], ray.o[1], ray.o[2], 1.0);
    cv::Mat x = A.inv() * b;

    double t = x.at<double>(3);
    if (t < 0.0 || MathUtil::isZero(t))
        return false;

    cv::Vec3d w(x.at<double>(0), x.at<double>(1), x.at<double>(2));
    if (w[0] < 0.0 || w[0] > 1.0 || w[1] < 0.0 || w[1] > 1.0 || w[2] < 0.0 || w[2] > 1.0)
        return false;

    return true;
}

bool Triangle::intersectsRay(const Ray& ray, IntersectionInfo* info) const
{
    if (info == nullptr)
        return intersectsRay(ray);

    if (startsRay(ray))
        return false;

    if (!aabb.intersectsRay(ray))
        return false;

    cv::Mat A = (cv::Mat_<double>(4, 4) <<
        vertices[0]->position[0], vertices[1]->position[0], vertices[2]->position[0], -ray.d[0],
        vertices[0]->position[1], vertices[1]->position[1], vertices[2]->position[1], -ray.d[1],
        vertices[0]->position[2], vertices[1]->position[2], vertices[2]->position[2], -ray.d[2],
        1.0, 1.0, 1.0, 0.0);

    cv::Mat b = (cv::Mat_<double>(4, 1) << ray.o[0], ray.o[1], ray.o[2], 1.0);
    cv::Mat x = A.inv() * b;

    double t = x.at<double>(3);
    if (t < 0.0 || MathUtil::isZero(t))
        return false;

    cv::Vec3d w(x.at<double>(0), x.at<double>(1), x.at<double>(2));
    if (w[0] < 0.0 || w[0] > 1.0 || w[1] < 0.0 || w[1] > 1.0 || w[2] < 0.0 || w[2] > 1.0)
        return false;

    info->ray = ray;
    info->t = t;
    cv::Vec3d position = w[0] * vertices[0]->position + w[1] * vertices[1]->position + w[2] * vertices[2]->position;
    cv::Vec3d normal = w[0] * vertices[0]->normal + w[1] * vertices[1]->normal + w[2] * vertices[2]->normal;
    info->vertex = Vertex(position, normal);
    
    return true;
}

void Triangle::computeAABB()
{
    double x[3] = { vertices[0]->position[0], vertices[1]->position[0], vertices[2]->position[0] };
    double y[3] = { vertices[0]->position[1], vertices[1]->position[1], vertices[2]->position[1] };
    double z[3] = { vertices[0]->position[2], vertices[1]->position[2], vertices[2]->position[2] };

    std::pair<double*, double*> boundX = std::minmax_element(x, x + 3);
    std::pair<double*, double*> boundY = std::minmax_element(y, y + 3);
    std::pair<double*, double*> boundZ = std::minmax_element(z, z + 3);

    aabb.minPoint[0] = *(boundX.first);
    aabb.minPoint[1] = *(boundY.first);
    aabb.minPoint[2] = *(boundZ.first);
    aabb.maxPoint[0] = *(boundX.second);
    aabb.maxPoint[1] = *(boundY.second);
    aabb.maxPoint[2] = *(boundZ.second);
}

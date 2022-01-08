#include "AABB.h"
#include "Utility/MathUtil.h"

bool AABB::enclosesPoint(const cv::Vec3d& point) const
{
    return (point[0] > minPoint[0] && point[0] < maxPoint[0])
        && (point[1] > minPoint[1] && point[1] < maxPoint[1])
        && (point[2] > minPoint[2] && point[2] < maxPoint[2]);
}

void AABB::reset()
{
    minPoint = cv::Vec3d(0.0, 0.0, 0.0);
    maxPoint = cv::Vec3d(0.0, 0.0, 0.0);
}

AABB::AABB()
{
    minPoint = cv::Vec3d(0.0, 0.0, 0.0);
    maxPoint = cv::Vec3d(0.0, 0.0, 0.0);
}

void AABB::merge(const AABB& aabb)
{
    if (aabb.minPoint[0] < minPoint[0])
        minPoint[0] = aabb.minPoint[0];
    if (aabb.minPoint[1] < minPoint[1])
        minPoint[1] = aabb.minPoint[1];
    if (aabb.minPoint[2] < minPoint[2])
        minPoint[2] = aabb.minPoint[2];

    if (aabb.maxPoint[0] > maxPoint[0])
        maxPoint[0] = aabb.maxPoint[0];
    if (aabb.maxPoint[1] > maxPoint[1])
        maxPoint[1] = aabb.maxPoint[1];
    if (aabb.maxPoint[2] > maxPoint[2])
        maxPoint[2] = aabb.maxPoint[2];
}

bool AABB::intersectsRay(const Ray& ray) const
{
    if (MathUtil::isZero(ray.d))
        return false;

    if (MathUtil::isZero(lengthX()) && MathUtil::isZero(lengthY()) && MathUtil::isZero(lengthZ()))
        return false;

    if (enclosesPoint(ray.o))
        return true;

    std::vector<double> tmin, tmax;// 沿各轴的交点
    std::vector<int> axisIndices;// 无交点的轴index

    for (int i = 0; i < 3; i++)
    {
        if (MathUtil::isZero(ray.d[i]))
        {
            axisIndices.push_back(i);
            continue;
        }

        double tin = (minPoint[i] - ray.o[i]) / ray.d[i];
        double tout = (maxPoint[i] - ray.o[i]) / ray.d[i];
        if (tin > tout)
            std::swap(tin, tout);
        if (tout < 0.0)
            return false;
        tmin.push_back(tin);
        tmax.push_back(tout);
    }

    double tEnter = *(std::max_element(tmin.begin(), tmin.end()));
    double tExit = *(std::min_element(tmax.begin(), tmax.end()));
    if (tEnter > tExit)
        return false;

    for (size_t i = 0; i < axisIndices.size(); i++)
    {
        int index = axisIndices[i];
        if (!(ray.o[index] > minPoint[index] && ray.o[index] < maxPoint[index]))
            return false;
    }

    return true;
}

double AABB::lengthX() const
{
    return std::abs(maxPoint[0] - minPoint[0]);
}

double AABB::lengthY() const
{
    return std::abs(maxPoint[1] - minPoint[1]);
}

double AABB::lengthZ() const
{
    return std::abs(maxPoint[2] - minPoint[2]);
}

cv::Vec3d AABB::center() const
{
    return 0.5 * (minPoint + maxPoint);
}

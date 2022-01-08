#include "Mesh.h"

void Mesh::computeAABB()
{
    aabb.reset();
    for (size_t i = 0; i < triangles.size(); i++)
    {
        aabb.merge(triangles[i].aabb);
    }
}

Mesh::Mesh(const std::vector<cv::Vec3d>& positions, const std::vector<cv::Vec3d>& normals, const std::vector<cv::Vec3i> indices)
{
    for (size_t i = 0; i < positions.size(); i++)
    {
        Vertex vertex(positions[i], normals[i]);
        vertices.push_back(vertex);
    }

    for (size_t i = 0; i < indices.size(); i++)
    {
        Triangle triangle(vertices[indices[i][0]], vertices[indices[i][1]], vertices[indices[i][2]]);
        triangles.push_back(triangle);
    }

    computeAABB();

    std::vector<int> triangleIndices(triangles.size());
    for (size_t i = 0; i < triangleIndices.size(); i++)
        triangleIndices[i] = int(i);
    rootBVH = new BVHNode(triangles, triangleIndices, nodeCollecter);
    nodeCollecter.push_back(rootBVH);
    rootBVH->createBVH();
}

Mesh::~Mesh()
{
    for (size_t i = 0; i < nodeCollecter.size(); i++)
        delete nodeCollecter[i];
    nodeCollecter.clear();
}

bool Mesh::intersectsRay(const Ray& ray) const
{
    return rootBVH->intersectsRay(ray);
}

bool Mesh::intersectsRay(const Ray& ray, IntersectionInfo* info) const
{
    if (info == nullptr)
        return intersectsRay(ray);

    return rootBVH->intersectsRay(ray, info);
}
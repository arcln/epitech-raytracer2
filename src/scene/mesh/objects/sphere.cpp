//
// sphere.cpp for rt in /home/arthur/B2/MUL/raytracer2/src/mesh/objects/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr  5 16:31:30 2017 Arthur Chaloin
// Last update Sun May 28 00:39:24 2017 Paul Laffitte
//
#include <iostream>
#include <memory>
#include "eq.hpp"
#include "objects/sphere.hpp"

rt::Intersection    rt::Sphere::intersect(rt::Ray const& ray, rt::Scene const *scene) const
{
    rt::Intersection inter;
    rt::Eq eq;

    eq.setA(ray.getDir() * ray.getDir());
    eq.setB(2 * ray.getDir().x * ray.getPos().x + 2 * ray.getDir().y * ray.getPos().y + 2 * ray.getDir().z * ray.getPos().z);
    eq.setC((ray.getPos() * ray.getPos()) - (this->getParam() * this->getParam()));
    inter.distance = eq.solve(scene);

    if (inter.distance != -1) {
        inter.hit.x = ray.getPos().x + (inter.distance * ray.getDir().x);
        inter.hit.y = ray.getPos().y + (inter.distance * ray.getDir().y);
        inter.hit.z = ray.getPos().z + (inter.distance * ray.getDir().z);
    }

    return inter;
}

rt::Vector3         rt::Sphere::getNormal(rt::Vector3 const& hit, __attribute__((unused))rt::Vector3 const& ray) const
{
    rt::Vector3 normal(hit);

    normal.normalize();
    return (this->computeBump(normal, hit));
}

void rt::Sphere::applyParameterOnVertices(std::vector<rt::Vector3> &vertices) const
{
    for (auto &vertice : vertices) {
        vertice = vertice * getParam();
    }
}

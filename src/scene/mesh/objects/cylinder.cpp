//
// sphere.cpp for rt in /home/arthur/B2/MUL/raytracer2/src/mesh/objects/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr  5 16:31:30 2017 Arthur Chaloin
// Last update Sun May 28 00:43:03 2017 Paul Laffitte
//
#include <iostream>
#include <memory>
#include "eq.hpp"
#include "objects/cylinder.hpp"

rt::Intersection    rt::Cylinder::intersect(rt::Ray const& ray, rt::Scene const *scene) const
{
    rt::Intersection inter;
    rt::Eq eq;

    eq.setA(SQUARE(ray.getDir().x) + SQUARE(ray.getDir().z));
    eq.setB((2 * ray.getPos().x * ray.getDir().x) + (2 * ray.getPos().z * ray.getDir().z));
    eq.setC(SQUARE(ray.getPos().x) + SQUARE(ray.getPos().z) - SQUARE(this->getParam()));
    inter.distance = eq.solve(scene);

    if (inter.distance != -1) {
        inter.hit.x = ray.getPos().x + (inter.distance * ray.getDir().x);
        inter.hit.y = ray.getPos().y + (inter.distance * ray.getDir().y);
        inter.hit.z = ray.getPos().z + (inter.distance * ray.getDir().z);
    }

    return inter;
}

rt::Vector3         rt::Cylinder::getNormal(rt::Vector3 const& hit, __attribute__((unused))rt::Vector3 const& ray) const
{
    rt::Vector3 normal(hit);

    normal.y = 0;
    normal.normalize();
    return this->computeBump(normal, hit);
}

void rt::Cylinder::applyParameterOnVertices(std::vector<rt::Vector3> &vertices) const
{
    for (auto &vertice : vertices) {
        vertice = vertice * getParam();
    }
}

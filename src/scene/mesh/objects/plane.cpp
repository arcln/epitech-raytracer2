//
// sphere.cpp for rt in /home/arthur/B2/MUL/raytracer2/src/mesh/objects/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr  5 16:31:30 2017 Arthur Chaloin
// Last update Sun May 28 14:23:43 2017 Paul Laffitte
//
#include <iostream>
#include <memory>
#include "eq.hpp"
#include "objects/plane.hpp"

rt::Intersection    rt::Plane::intersect(rt::Ray const& ray, rt::Scene const *scene) const
{
    rt::Intersection inter;

    inter.distance = (-ray.getPos().y / ray.getDir().y <= 0 ? -1.0f : -ray.getPos().y / ray.getDir().y);
    if (inter.distance <= scene->getEpsilon()) {
        inter.distance = -1;
    }

    if (inter.distance != -1) {
        inter.hit.x = ray.getPos().x + (inter.distance * ray.getDir().x);
        inter.hit.y = ray.getPos().y + (inter.distance * ray.getDir().y);
        inter.hit.z = ray.getPos().z + (inter.distance * ray.getDir().z);
    }

    return inter;
}

rt::Vector3         rt::Plane::getNormal(rt::Vector3 const& hit, __attribute__((unused))rt::Vector3 const& ray) const
{
  return this->computeBump(rt::Vector3(0, 1, 0), hit);
}

void rt::Plane::applyParameterOnVertices(std::vector<rt::Vector3> &vertices) const
{
    (void)vertices;
}

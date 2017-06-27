//
// sphere.cpp for rt in /home/arthur/B2/MUL/raytracer2/src/mesh/objects/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr  5 16:31:30 2017 Arthur Chaloin
// Last update Sun May 28 14:23:50 2017 Paul Laffitte
//
#include <iostream>
#include <memory>
#include "eq.hpp"
#include "objects/triangle.hpp"

rt::Intersection    rt::Triangle::intersect(rt::Ray const& ray, rt::Scene const *scene) const
{
    rt::Intersection inter;
    rt::Vector3	tnormal;
    rt::Vector3	dir;
    float		alpha;
    float		beta;
    float		gamma;
    float		area;

    tnormal = rt::Vector3(this->top[1].x - this->top[0].x,
  	                      this->top[1].y - this->top[0].y,
  	                      this->top[1].z - this->top[0].z);
    tnormal = tnormal.cross(rt::Vector3(this->top[2].x - this->top[0].x,
  	                                    this->top[2].y - this->top[0].y,
  	                                    this->top[2].z - this->top[0].z));
    dir = rt::Vector3(
        this->top[0].x - ray.getPos().x,
        this->top[0].y - ray.getPos().y,
        this->top[0].z - ray.getPos().z
    );

    inter.distance = (dir * tnormal) / (ray.getDir() * tnormal);
    if (inter.distance < 0 || !(tnormal * ray.getDir())) {
        inter.distance = -1;
    }
    inter.hit.x = ray.getPos().x + (inter.distance * ray.getDir().x);
    inter.hit.y = ray.getPos().y + (inter.distance * ray.getDir().y);
    inter.hit.z = ray.getPos().z + (inter.distance * ray.getDir().z);
    area = tnormal.len();

    rt::Vector3 tmp(this->top[0].x - inter.hit.x,
  			        this->top[0].y - inter.hit.y,
  			        this->top[0].z - inter.hit.z);
    tmp = tmp.cross(rt::Vector3(this->top[1].x - inter.hit.x,
                                this->top[1].y - inter.hit.y,
                                this->top[1].z - inter.hit.z));
    alpha = tmp.len() / area;
    if (alpha < 0. || alpha > 1.) {
        inter.distance = -1;
    }

    tmp = rt::Vector3(this->top[0].x - inter.hit.x,
  			          this->top[0].y - inter.hit.y,
  			          this->top[0].z - inter.hit.z);
    tmp = tmp.cross(rt::Vector3(this->top[2].x - inter.hit.x,
                    this->top[2].y - inter.hit.y,
                    this->top[2].z - inter.hit.z));
    beta = tmp.len() / area;
    if (beta < 0. || alpha + beta > 1.)
      inter.distance = -1;

    tmp = rt::Vector3(this->top[1].x - inter.hit.x,
  			   this->top[1].y - inter.hit.y,
  			   this->top[1].z - inter.hit.z);
    tmp = tmp.cross(rt::Vector3(this->top[2].x - inter.hit.x,
                    this->top[2].y - inter.hit.y,
                    this->top[2].z - inter.hit.z));
    gamma = tmp.len() / area;
    if (gamma < 0. || gamma > 1. || alpha + beta + gamma < 0.98 ||
        alpha + beta + gamma > 1.02 || inter.distance < scene->getEpsilon()) {
            inter.distance = -1;
    }

    if (inter.distance != -1) {
        inter.hit.x = ray.getPos().x + (inter.distance * ray.getDir().x);
        inter.hit.y = ray.getPos().y + (inter.distance * ray.getDir().y);
        inter.hit.z = ray.getPos().z + (inter.distance * ray.getDir().z);
    }

    return inter;
}

rt::Vector3         rt::Triangle::getNormal(rt::Vector3 const& hit, rt::Vector3 const& ray) const
{
    rt::Vector3 normal;

    normal = rt::Vector3(this->top[1].x - this->top[0].x,
  	                     this->top[1].y - this->top[0].y,
  	                     this->top[1].z - this->top[0].z);
    normal = normal.cross(rt::Vector3(this->top[2].x - this->top[0].x,
                          this->top[2].y - this->top[0].y,
                          this->top[2].z - this->top[0].z));
    normal.normalize();

    if (ray * normal < 0) {
        normal.x *= -1;
        normal.y *= -1;
        normal.z *= -1;
    }

    return this->computeBump(normal, hit);
}

void rt::Triangle::applyParameterOnVertices(std::vector<rt::Vector3> &vertices) const
{
    (void)vertices;
}

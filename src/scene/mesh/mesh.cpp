//
// mesh.cpp for rt in /Users/arthur/Documents/Dev/Epitech/MUL/raytracer2/src/scene/mesh/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Fri May 26 18:30:26 2017 Arthur Chaloin
// Last update Sun May 28 13:37:22 2017 Thomas ARBONA
//

#include <cmath>
#include "mesh.hpp"
#include "perlin.hpp"
#include "vector.hpp"

void rt::AMesh::addPosition(rt::Vector3 const& pos)
{
    rt::Matrix transform;

    transform.init();
    transform[0][3] = pos.x;
    transform[1][3] = pos.y;
    transform[2][3] = pos.z;
    matrix = matrix * transform;
}

void rt::AMesh::addRotation(rt::Vector3 angle)
{
    rt::Matrix transform;

    transform.init();
    angle.x *= M_PI / 180.;
    angle.y *= M_PI / 180.;
    angle.z *= M_PI / 180.;

    transform[1][1] = cos(angle.x);
    transform[1][2] = -sin(angle.x);
    transform[2][1] = sin(angle.x);
    transform[2][2] = cos(angle.x);
    matrix = matrix * transform;
    transform.init();
    transform[0][0] = cos(angle.y);
    transform[0][2] = sin(angle.y);
    transform[2][0] = -sin(angle.y);
    transform[2][2] = cos(angle.y);
    matrix = matrix * transform;
    transform.init();
    transform[0][0] = cos(angle.z);
    transform[0][1] = -sin(angle.z);
    transform[1][0] = sin(angle.z);
    transform[1][1] = cos(angle.z);
    matrix = matrix * transform;
}

rt::Vector3
rt::AMesh::computeBump(rt::Vector3 normal, rt::Vector3 const& hit) const
{
  float r = this->getBumpScale();
  float bump = this->getBump();

  if (bump != 0.) {
    float x = rt::Perlin::getValue(r * hit.x - bump, r * hit.y, r * hit.z) -
      rt::Perlin::getValue(r * hit.x + bump, r * hit.y, r * hit.z);
    float y = rt::Perlin::getValue(r * hit.x, r * hit.y - bump, r * hit.z) -
      rt::Perlin::getValue(r * hit.x, r * hit.y + bump, r * hit.z);
    float z = rt::Perlin::getValue(r * hit.x, r * hit.y, r * hit.z - bump) -
      rt::Perlin::getValue(r * hit.x, r * hit.y, r * hit.z + bump);

    normal.x += x;
    normal.y += y;
    normal.z += z;
    normal.normalize();
  }

  return normal;
}

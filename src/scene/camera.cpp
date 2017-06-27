//
// camera.cpp for rt in /Users/arthur/Documents/Dev/Epitech/MUL/raytracer2/src/scene/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Fri May 26 18:54:39 2017 Arthur Chaloin
// Last update Sun May 28 15:26:41 2017 Paul Laffitte
//

#include <cmath>
#include "camera.hpp"
#include "vector.hpp"

void rt::Camera::addPosition(rt::Vector3 const& pos) {
    rt::Matrix transform;

    transform.init();
    transform[0][3] = pos.x;
    transform[1][3] = pos.y;
    transform[2][3] = pos.z;
    matrix = matrix * transform;
    _position.multMatrix(transform, 1);
}

void rt::Camera::addRotation(rt::Vector3 angle) {
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
    _lookAt.multMatrix(transform, 0);
}

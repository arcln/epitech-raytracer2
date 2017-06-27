//
// ray.cpp for rt in /home/arthur/B2/MUL/raytracer2/src/ray/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr  5 15:36:37 2017 Arthur Chaloin
// Last update Sat May 27 17:12:09 2017 Arthur Chaloin
//
#include <iostream>
#include <unistd.h>
#include <cmath>
#include "scene.hpp"
#include "ray.hpp"

rt::Ray::Ray(rt::Vector3 const& __pos, rt::Vector3 const& __dir)
{
    this->_position = __pos;
    this->_direction = __dir;
}

void rt::Ray::raytrace(rt::Camera const& camera, sf::Vector2i const& pos)
{
    sf::Vector2f truePos;

    _position.x = 0;
    _position.y = 0;
    _position.z = 0;
    truePos.x = (float)pos.x + (float)rand() / (float)(RAND_MAX);
    truePos.y = (float)pos.y + (float)rand() / (float)(RAND_MAX);
    _direction.x = ((float)(truePos.x / (float)WIDTH) * 2.) - 1.;
    _direction.y = -(((float)(truePos.y / (float)HEIGHT) * 2.) - 1.);
    _direction.z = camera.screen_dist;
}

void rt::Ray::computeCamera(rt::Camera const& camera)
{
    _direction.normalize();
    _position.multMatrix(camera.matrix, 1);
    _direction.multMatrix(camera.matrix, 0);
}

void rt::Ray::compute(rt::AMesh const *mesh)
{
    _direction.normalize();
    _position.multMatrix(mesh->invMatrix, 1);
    _direction.multMatrix(mesh->invMatrix, 0);
    _direction.normalize();
}

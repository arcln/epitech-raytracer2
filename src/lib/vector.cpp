//
// vector.cpp for rt in /home/arthur/B2/MUL/raytracer2/src/lib/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Fri Mar 24 10:55:25 2017 John Doe
// Last update Sat May 27 16:08:31 2017 Arthur Chaloin
//
#include <iostream>
#include <math.h>
#include "matrix.hpp"
#include "vector.hpp"

rt::Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float           rt::Vector3::len()
{
    return sqrt((x * x) + (y * y) + (z * z));
}

void            rt::Vector3::normalize()
{
    float   len = this->len();

    if (!len) {
        std::cerr << "Warning: division by zero when normalizing." << std::endl;
    }
    this->x /= len;
    this->y /= len;
    this->z /= len;
}

float           rt::Vector3::operator *(Vector3 const& vec) const
{
    return (this->x * vec.x) + (this->y * vec.y) + (this->z * vec.z);
}

rt::Vector3     rt::Vector3::operator *(float const& value) const
{
    Vector3 result;

    result.x = this->x * value;
    result.y = this->y * value;
    result.z = this->z * value;

    return result;
}

rt::Vector3     rt::Vector3::operator /(float const& value) const
{
    Vector3 result;

    result.x = this->x / value;
    result.y = this->y / value;
    result.z = this->z / value;

    return result;
}

rt::Vector3     rt::Vector3::operator +(Vector3 const& vec)
{
    rt::Vector3 result;

    result.x = this->x + vec.x;
    result.y = this->y + vec.y;
    result.z = this->z + vec.z;

    return result;
}

rt::Vector3     rt::Vector3::operator -(Vector3 const& vec)
{
    rt::Vector3 result;

    result.x = this->x - vec.x;
    result.y = this->y - vec.y;
    result.z = this->z - vec.z;

    return result;
}

float rt::Vector3::getDist(rt::Vector3 v)
{
  return (sqrt((this->x - v.x) * (this->x - v.x) +
	       (this->y - v.y) * (this->y - v.y) +
	       (this->z - v.z) * (this->z - v.z)));
}

rt::Vector3     rt::Vector3::cross(Vector3 const& vec)
{
    Vector3 result;

    result.x = this->y * vec.z - (this->z * vec.y);
    result.y = this->z * vec.x - (this->x * vec.z);
    result.z = this->x * vec.y - (this->y * vec.x);

    return result;
}

void rt::Vector3::multMatrix(rt::Matrix const& matrix, int w)
{
    float vec[4], result[4];

    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
    vec[3] = w;
    result[0] = matrix[0][0] * vec[0] + matrix[0][1] * vec[1] + matrix[0][2] * vec[2] + matrix[0][3] * vec[3];
    result[1] = matrix[1][0] * vec[0] + matrix[1][1] * vec[1] + matrix[1][2] * vec[2] + matrix[1][3] * vec[3];
    result[2] = matrix[2][0] * vec[0] + matrix[2][1] * vec[1] + matrix[2][2] * vec[2] + matrix[2][3] * vec[3];
    result[3] = matrix[3][0] * vec[0] + matrix[3][1] * vec[1] + matrix[3][2] * vec[2] + matrix[3][3] * vec[3];
    x = result[0];
    y = result[1];
    z = result[2];
}

void rt::Vector3::print() const
{
    std::cout << x << " " << y << " " << z << std::endl;
}

void rt::Vector3::print(std::string const& context) const
{
    std::cout << context << " " << x << " " << y << " " << z << std::endl;
}

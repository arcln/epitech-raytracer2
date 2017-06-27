//
// matrix.cpp for rt in /home/arthur/B2/MUL/raytracer2/src/lib/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Thu Apr 13 13:02:36 2017 Arthur Chaloin
// Last update Thu May 25 19:53:31 2017 Arthur Chaloin
//
#include <iostream>
#include "matrix.hpp"
#include "vector.hpp"

void rt::Matrix::init()
{
    _data[0][0] = 1;
    _data[0][1] = 0;
    _data[0][2] = 0;
    _data[0][3] = 0;
    _data[1][0] = 0;
    _data[1][1] = 1;
    _data[1][2] = 0;
    _data[1][3] = 0;
    _data[2][0] = 0;
    _data[2][1] = 0;
    _data[2][2] = 1;
    _data[2][3] = 0;
    _data[3][0] = 0;
    _data[3][1] = 0;
    _data[3][2] = 0;
    _data[3][3] = 1;
}

void rt::Matrix::print() const
{
    std::cout << "===========================" << std::endl;
    for (auto index = 0; index < 4; index++) {
        for (auto index2 = 0; index2 < 4; index2++) {
            std::cout << _data[index][index2] << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void rt::Matrix::print(std::string const& context) const
{
    std::cout << "====== " << context << " ======" <<std::endl;
    for (auto index = 0; index < 4; index++) {
        for (auto index2 = 0; index2 < 4; index2++) {
            std::cout << _data[index][index2] << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

rt::Matrix rt::Matrix::operator *(rt::Matrix const& m)
{
    rt::Matrix result;

    result[0][0] = _data[0][0] * m[0][0] + _data[0][1] * m[1][0] + _data[0][2] * m[2][0] + _data[0][3] * m[3][0];
    result[0][1] = _data[0][0] * m[0][1] + _data[0][1] * m[1][1] + _data[0][2] * m[2][1] + _data[0][3] * m[3][1];
    result[0][2] = _data[0][0] * m[0][2] + _data[0][1] * m[1][2] + _data[0][2] * m[2][2] + _data[0][3] * m[3][2];
    result[0][3] = _data[0][0] * m[0][3] + _data[0][1] * m[1][3] + _data[0][2] * m[2][3] + _data[0][3] * m[3][3];
    result[1][0] = _data[1][0] * m[0][0] + _data[1][1] * m[1][0] + _data[1][2] * m[2][0] + _data[1][3] * m[3][0];
    result[1][1] = _data[1][0] * m[0][1] + _data[1][1] * m[1][1] + _data[1][2] * m[2][1] + _data[1][3] * m[3][1];
    result[1][2] = _data[1][0] * m[0][2] + _data[1][1] * m[1][2] + _data[1][2] * m[2][2] + _data[1][3] * m[3][2];
    result[1][3] = _data[1][0] * m[0][3] + _data[1][1] * m[1][3] + _data[1][2] * m[2][3] + _data[1][3] * m[3][3];
    result[2][0] = _data[2][0] * m[0][0] + _data[2][1] * m[1][0] + _data[2][2] * m[2][0] + _data[2][3] * m[3][0];
    result[2][1] = _data[2][0] * m[0][1] + _data[2][1] * m[1][1] + _data[2][2] * m[2][1] + _data[2][3] * m[3][1];
    result[2][2] = _data[2][0] * m[0][2] + _data[2][1] * m[1][2] + _data[2][2] * m[2][2] + _data[2][3] * m[3][2];
    result[2][3] = _data[2][0] * m[0][3] + _data[2][1] * m[1][3] + _data[2][2] * m[2][3] + _data[2][3] * m[3][3];
    result[3][0] = _data[3][0] * m[0][0] + _data[3][1] * m[1][0] + _data[3][2] * m[2][0] + _data[3][3] * m[3][0];
    result[3][1] = _data[3][0] * m[0][1] + _data[3][1] * m[1][1] + _data[3][2] * m[2][1] + _data[3][3] * m[3][1];
    result[3][2] = _data[3][0] * m[0][2] + _data[3][1] * m[1][2] + _data[3][2] * m[2][2] + _data[3][3] * m[3][2];
    result[3][3] = _data[3][0] * m[0][3] + _data[3][1] * m[1][3] + _data[3][2] * m[2][3] + _data[3][3] * m[3][3];

    return result;
}

void rt::Matrix::invert()
{
    int i, j, k, l;
    rt::Matrix mat(*this);

    this->init();
    k = 0;
    i = -1;
    while (++i < 4 || (i = 0) || ++k < 4) {
        if (i == k) {
            i++;
        }
        if (i == 4) {
            break;
        }
        j = -1;
        l = mat[i][k];
        while (++j < 4) {
            mat[i][j] = l * mat[k][j] - mat[k][k] * mat[i][j];
            _data[i][j] = l * _data[k][j] - mat[k][k] * _data[i][j];
        }
    }
    i = 0;
    j = -1;
    while (++j < 4 || (j = 0) || ++i < 4) {
        _data[i][j] /= mat[i][i];
    }
}

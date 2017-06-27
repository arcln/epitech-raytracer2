//
// eq.cpp for rt in /home/arthur/B2/MUL/raytracer2/src/lib/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr 12 16:56:13 2017 Arthur Chaloin
// Last update Tue May 23 18:22:31 2017 Arthur Chaloin
//
#include <iostream>
#include <math.h>
#include "scene.hpp"
#include "eq.hpp"

float rt::Eq::solve(rt::Scene const *scene)
{
    float result;
    float delta = (_b * _b) - (4 * _a * _c);

    if (delta < 0) {
        result = -1;
    }
    else if (delta == 0) {
        result = (-_b / (2 * _a));
        if (result < scene->getEpsilon()) {
            result = -1;
        }
    }
    else {
        result = MIN(((-_b - sqrt(delta)) / (2 * _a)), ((-_b + sqrt(delta)) / (2 * _a)));
        if (result < scene->getEpsilon()) {
  	         result = MAX(((-_b - sqrt(delta)) / (2 * _a)), ((-_b + sqrt(delta)) / (2 * _a)));
             if (result < scene->getEpsilon()) {
                 result = -1;
             }
  	    }
    }
    return result;
}

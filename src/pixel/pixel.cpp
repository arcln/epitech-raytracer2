//
// pixel.cpp for rt in /home/arthur/B2/MUL/raytracer2/src/pixel/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr 12 19:38:43 2017 Arthur Chaloin
// Last update Sun May 28 20:06:31 2017 Arthur Chaloin
//
#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "pixel.hpp"
#include "ray.hpp"
#include "texture.hpp"

void rt::Pixel::computeReflection(rt::Scene const& scene,
                                    rt::AMesh const *obj,
                                    rt::Intersection inter,
                                    rt::Ray ray,
                                    int const level)
{
    rt::Vector3 normal;
    sf::Color color, newColor;
    float coef;

    normal = obj->getNormal(inter.hit, ray.getDir());
    normal.x = -normal.x;
    normal.y = -normal.y;
    normal.z = -normal.z;
    normal.multMatrix(obj->matrix, 0);
    inter.hit.multMatrix(obj->matrix, 1);
    ray.setPos(inter.hit);
    ray.getDir().multMatrix(obj->matrix, 0);
    coef = 2.f * (ray.getDir() * normal);
    ray.setDir(rt::Vector3(ray.getDir().x - (coef * normal.x),
    			           ray.getDir().y - (coef * normal.y),
      			           ray.getDir().z - (coef * normal.z)));
    ray.getDir().normalize();
    this->computeColor(scene, ray, level + 1);

    newColor.r = (float)_color.r * ((float)obj->getReflectLevel() / 100.);
    newColor.g = (float)_color.g * ((float)obj->getReflectLevel() / 100.);
    newColor.b = (float)_color.b * ((float)obj->getReflectLevel() / 100.);
    newColor.r += (float)obj->getColor().r * ((float)(100 - obj->getReflectLevel()) / 100.);
    newColor.g += (float)obj->getColor().g * ((float)(100 - obj->getReflectLevel()) / 100.);
    newColor.b += (float)obj->getColor().b * ((float)(100 - obj->getReflectLevel()) / 100.);
    _color = newColor;
}

void rt::Pixel::computeRefraction(rt::Scene const& scene,
                                    rt::AMesh const *obj,
                                    rt::Intersection inter,
                                    rt::Ray ray,
                                    int const level)
{
    float coef, coefRefract, indiceI, indiceT, k, cosI, sinT, cosT, rs, rp;
    rt::Vector3 normal;
    sf::Color color, newColor;

    normal = obj->getNormal(inter.hit, ray.getDir());
    normal.multMatrix(obj->matrix, 0);
    inter.hit.multMatrix(obj->matrix, 1);
    ray.setPos(inter.hit);
    ray.getDir().multMatrix(obj->matrix, 0);

    cosI = ray.getDir() * normal;
    if (cosI > 0) {
        indiceI = 1.0;
        indiceT = obj->getRefractIndice();
    } else {
        indiceI = obj->getRefractIndice();
        indiceT = 1.0;
        cosI = -cosI;
    }
    coef = indiceI / indiceT;
    k = 1 - coef * coef * (1 - cosI * cosI);
    if (k < 0) {
      return ;
    }
    ray.setDir(rt::Vector3(ray.getDir().x * coef + (coef * cosI - sqrtf(k)) * normal.x,
                          ray.getDir().y * coef + (coef * cosI - sqrtf(k)) * normal.y,
                          ray.getDir().z * coef + (coef * cosI - sqrtf(k)) * normal.z));
    ray.getDir().normalize();

    this->computeColor(scene, ray, level + 1);

    sinT = indiceI / indiceT * sqrtf(std::max(0.0, 1.0 - cosI * cosI));
    if (sinT >= 1) {
        coefRefract = 1;
    } else {
        cosT = sqrtf(std::max(0.0, 1.0 - sinT * sinT));
        cosI = fabsf(cosI);
        rs = ((indiceT * cosI) - (indiceI * cosT)) / ((indiceT * cosI) + (indiceI * cosT));
        rp = ((indiceI * cosI) - (indiceT * cosT)) / ((indiceI * cosI) + (indiceT * cosT));
        coefRefract = (rs * rs + rp * rp) * 0.5;
    }

    newColor.r = (float)_color.r * coefRefract;
    newColor.g = (float)_color.g * coefRefract;
    newColor.b = (float)_color.b * coefRefract;
    newColor.r += (float)obj->getColor().r * (1 - coefRefract);
    newColor.g += (float)obj->getColor().g * (1 - coefRefract);
    newColor.b += (float)obj->getColor().b * (1 - coefRefract);
    _color = newColor;
}

void rt::Pixel::addLight(rt::AMesh const *obj, rt::Light *light, float coef, rt::Vector3 const& pos)
{
  sf::Color objClr, lightClr;
  float r, g, b;

  coef = (coef < 0.) ? 0. : (coef > 1.) ? 1. : coef;
  if (obj->getTexture() != rt::TextureType::None)
    objClr = rt::Texture::get(obj, pos.x, pos.y, pos.z);
  else
    objClr = obj->getColor();
  lightClr = light->getColor();
  coef *= light->getPower();
  r = ((float)objClr.r / 255. * (float)lightClr.r / 255.) * coef * 255;
  g = ((float)objClr.g / 255. * (float)lightClr.g / 255.) * coef * 255;
  b = ((float)objClr.b / 255. * (float)lightClr.b / 255.) * coef * 255;
  this->_color.r = (this->_color.r + r > 255) ? 255 : this->_color.r + r;
  this->_color.g = (this->_color.g + g > 255) ? 255 : this->_color.g + g;
  this->_color.b = (this->_color.b + b > 255) ? 255 : this->_color.b + b;
}

void rt::Pixel::computeLight(rt::Scene const& scene, rt::AMesh const *obj, rt::Intersection inter)
{
  std::vector<rt::Light *> lights;
  rt::Vector3 baseHit(inter.hit);
  float dist;

  inter.hit.multMatrix(obj->matrix, 1);
  lights = scene.getLights();

  this->_color = (sf::Color){0, 0, 0, 255};
  for (auto it = lights.begin(); it != lights.end(); ++it) {
    rt::Vector3 rayDir, pos;
    rt::Ray rayLight;

    pos = inter.hit;
    float finalCoef = 0.f;

    for (int i = 0; i < SMOOTH_LEVEL; i++) {
        rayLight.setPos(pos);
        rayDir = (*it)->getPos() - pos;
        rayDir.x += fmodf((float)rand(), ((float)SMOOTH_POWER / 50.f)) - ((float)SMOOTH_POWER / 100.f);
        rayDir.y += fmodf((float)rand(), ((float)SMOOTH_POWER / 50.f)) - ((float)SMOOTH_POWER / 100.f);
        rayDir.z += fmodf((float)rand(), ((float)SMOOTH_POWER / 50.f)) - ((float)SMOOTH_POWER / 100.f);
        rayLight.setDir(rayDir);
        rayLight.getDir().normalize();

        rt::Vector3 normal = obj->getNormal(baseHit, rayLight.getDir());
        normal.multMatrix(obj->matrix, 0);

        float coef = rayLight.getDir() * normal;

        if ((dist = scene.getInterDist(rayLight)) > 0.0 &&
    	   dist < rayLight.getPos().getDist((*it)->getPos())) {
               coef = 0.0;
        }

        finalCoef += coef;
    }
    finalCoef /= (float)SMOOTH_LEVEL;
    this->addLight(obj, *it, finalCoef, inter.hit);
  }
}

void rt::Pixel::computeColor(rt::Scene const& scene, rt::Ray const& base, int recursionLevel)
{
    rt::Intersection inter, min;
    rt::AMesh *obj = nullptr;
    rt::Ray objRay, ray;

    min.distance = INT_MAX;
    std::vector<AMesh *> objs = scene.getObjs();
    for (auto it = objs.begin(); it != objs.end(); ++it) {
        ray = base;
        ray.compute(*it);
        inter = (*it)->intersect(ray, &scene);

        if (inter.distance != -1 && inter.distance < min.distance) {
            min.distance = inter.distance;
            min.hit = inter.hit;
            obj = *it;
            objRay = ray;
        }
    }

    if (min.distance != INT_MAX) {
        _color = obj->getColor();
        this->computeLight(scene, obj, min);
        if (obj->getReflectLevel() && recursionLevel < MAX_RECURSION_LEVEL) {
            this->computeReflection(scene, obj, min, objRay, recursionLevel);
        }
    } else {
        _color = sf::Color(0, 0, 0, 0);
    }
}

void rt::Pixel::compute(rt::Scene const& scene, sf::Vector2i const& pos)
{
    rt::Ray ray;

    ray.raytrace(scene.getCamera(), pos);
    ray.computeCamera(scene.getCamera());

    this->computeColor(scene, ray);
}

//
// texture.cpp for rt in /home/arbona/tek1/MUL/raytracer2
//
// Made by Thomas ARBONA
// Login   <thomas.arbona@epitech.eu>
//
// Started on  Sat May 27 19:58:14 2017 Thomas ARBONA
// Last update Sun May 28 15:30:56 2017 Arthur Chaloin
//
#include <SFML/Graphics.hpp>
#include <cmath>
#include "perlin.hpp"
#include "mesh.hpp"
#include "texture.hpp"

rt::TextureFunc g_textureFunc[] = {
  {rt::TextureType::Wood, rt::Texture::getWood},
  {rt::TextureType::Marble, rt::Texture::getMarble},
  {rt::TextureType::Perlin, rt::Texture::getPerlin},
  {rt::TextureType::None, 0}
};

rt::TextureColors g_textureColors[] = {
  {rt::TextureType::Wood, sf::Color(182, 155, 76, 255), sf::Color(130, 82, 1, 255)},
  {rt::TextureType::Marble, sf::Color(43, 44, 67, 255), sf::Color(130, 135, 224, 255)},
  {rt::TextureType::None, sf::Color(), sf::Color()}
};

sf::Color
rt::Texture::getWood(AMesh const*& obj, const float& x, const float& y, const float& z)
{
  sf::Color color;
  rt::TextureColors colors = rt::Texture::getColors(rt::TextureType::Wood);
  float n = 20 * rt::Perlin::getValue(x, y, z);

  (void)obj;
  n -= floorf(n);

  color.r = colors.min.r * n + colors.max.r * (1 - n);
  color.g = colors.min.g * n + colors.max.g * (1 - n);
  color.b = colors.min.b * n + colors.max.b * (1 - n);
  color.a = 255;
  if (rand() % 2 == 0)
    {
      color.r += 20;
      color.g += 20;
      color.b += 20;
    }
  return (color);
}

sf::Color
rt::Texture::getMarble(AMesh const*& obj, const float& x, const float& y, const float& z)
{
  sf::Color color;
  rt::TextureColors colors = rt::Texture::getColors(rt::TextureType::Marble);
  float ratio = 15.;
  float n = rt::Perlin::getValue(x * ratio, y * ratio, z * ratio);

  (void)obj;
  n = cos((x * ratio) + n);

  if (n < 0)
    color = colors.max;
  else
    {
      color.r = colors.min.r * n + colors.max.r * (1 - n);
      color.g = colors.min.g * n + colors.max.g * (1 - n);
      color.b = colors.min.b * n + colors.max.b * (1 - n);
      color.a = 255;
    }
  if (rand() % 2 == 0)
    {
      color.r += n < 0 ? 20 : -10;
      color.g += n < 0 ? 20 : -10;
      color.b += n < 0 ? 20 : -10;
    }
  return (color);
}

sf::Color
rt::Texture::getPerlin(AMesh const*& obj, const float& x, const float& y, const float& z)
{
  sf::Color color, min, max;
  float ratio = 10.;
  float n = rt::Perlin::getValue(x * ratio, y * ratio, z * ratio);

  min = obj->getColor();
  max.r = 255 - min.r;
  max.g = 255 - min.g;
  max.b = 255 - min.b;

  color.r = min.r * n + max.r * (1 - n);
  color.g = min.g * n + max.g * (1 - n);
  color.b = min.b * n + max.b * (1 - n);
  color.a = 255;

  return (color);
}

rt::TextureColors
  rt::Texture::getColors(rt::TextureType type)
{
  int index = 0;

  while (g_textureColors[index].type != rt::TextureType::None)
    {
      if (g_textureColors[index].type == type)
	break;
      index += 1;
    }
  return (g_textureColors[index]);
}

sf::Color
rt::Texture::get(AMesh const*& obj, const float& x, const float& y, const float& z)
{
  rt::TextureType type = obj->getTexture();
  int index = 0;

  while (g_textureFunc[index].type != rt::TextureType::None)
    {
      if (g_textureFunc[index].type == type)
	return (g_textureFunc[index].func(obj, x, y, z));
      index += 1;
    }
  return (sf::Color(0, 0, 0, 255));
}

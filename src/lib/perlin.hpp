//
// perlin.hpp for rt in /home/arbona/tek1/MUL/raytracer2
//
// Made by Thomas ARBONA
// Login   <thomas.arbona@epitech.eu>
//
// Started on  Sat May 27 17:23:48 2017 Thomas ARBONA
// Last update Sat May 27 17:56:07 2017 Thomas ARBONA
//
#ifndef PERLIN_HPP_
# define PERLIN_HPP_

namespace rt
{
  class Vector3;
  class Perlin
  {
  public:
    static float __attribute__((pure)) getValue(float x, float y, float z);

  private:
    static float __attribute__ ((pure)) dot3(const char a[], float x, float y, float z);
    static float __attribute__ ((const)) lerp(float a, float b, float t);
    static float __attribute__ ((const)) fade(float n);
    static float __attribute__((pure)) getValue2(unsigned int gi[8], rt::Vector3 r, rt::Vector3 f);
    Perlin(){};
  };
}

# define FLOOR(x)	(((x) >= 0) ? (int)(x) : (int)(x) - 1)

#endif /* !PERLIN_HPP_ */

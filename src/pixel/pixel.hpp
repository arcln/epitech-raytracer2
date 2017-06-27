//
// pixel.hpp for rt in /home/arthur/B2/MUL/raytracer2/src/pixel/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr 12 19:33:01 2017 Arthur Chaloin
// Last update Sun May 28 20:05:26 2017 Arthur Chaloin
//

#ifndef PIXEL_HPP_
# define PIXEL_HPP_

# include <SFML/Graphics.hpp>
# include "scene.hpp"

# define MAX_RECURSION_LEVEL 1

namespace rt
{
  class Vector3;
    class Pixel
    {
    public:
        Pixel() = default;
        Pixel(rt::Pixel const&) = default;
        rt::Pixel &operator =(rt::Pixel const&) = default;
        ~Pixel() = default;

        sf::Color getColor() const {return _color;}

        void compute(rt::Scene const&, sf::Vector2i const&);
        void computeLight(rt::Scene const&, rt::AMesh const *, rt::Intersection);
        void addLight(rt::AMesh const *obj, rt::Light *light, float coef, rt::Vector3 const& pos);
        void computeColor(rt::Scene const&, rt::Ray const&, int recursionLevel = 0);
        void computeReflection(rt::Scene const& scene, rt::AMesh const *obj, rt::Intersection inter, rt::Ray ray, int const level);
        void computeRefraction(rt::Scene const& scene, rt::AMesh const *obj, rt::Intersection inter, rt::Ray ray, int const level);

    private:
        sf::Color _color;
    };
}

#endif /* !PIXEL_HPP_ */

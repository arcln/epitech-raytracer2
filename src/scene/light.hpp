//
// light.hpp for rt in /home/arthur/B2/MUL/raytracer2/src/scene/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Thu Apr 13 17:30:57 2017 Arthur Chaloin
// Last update Fri May 26 18:49:47 2017 Arthur Chaloin
//

#ifndef LIGHT_HPP_
# define LIGHT_HPP_

# include "vector.hpp"
# include <SFML/Graphics.hpp>

namespace rt
{
    class Light
    {
    public:
        Light() = default;
        Light(rt::Light const&) = default;
        rt::Light &operator =(rt::Light const&) = default;
        ~Light() = default;

        rt::Vector3 getPos() const {return _position;}
        void setPos(rt::Vector3 const& __pos) {_position = __pos;}

        float getPower() const {return _power;}
        void setPower(float __power) {_power = __power;}

        sf::Color getColor() const {return _color;}
        void setColor(sf::Color const& __color) {_color = __color;}

    private:
        rt::Vector3 _position{0, 0, 0};
        sf::Color _color{255, 255, 255, 255};
        float _power = 1.f;
    };
}

#endif /* !LIGHT_HPP_ */

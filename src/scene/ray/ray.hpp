//
// ray.hpp for rt in /home/arthur/B2/MUL/raytracer2/src/ray/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr  5 15:24:35 2017 Arthur Chaloin
// Last update Sat May 27 18:34:21 2017 Alexandre Chamard-bois
//

#ifndef RAY_HPP_
# define RAY_HPP_

# include <SFML/Graphics.hpp>
# include "camera.hpp"
# include "vector.hpp"
# include "mesh.hpp"


namespace rt
{
    struct Intersection {
        float       distance;
        rt::Vector3 hit;
    };

    class AMesh;

    class Ray
    {
    public:
        Ray() = default;
        Ray(rt::Vector3 const&, rt::Vector3 const&);
        Ray(rt::Ray const& ray) {_position = ray.getPos(); _direction = ray.getDir();};
        virtual ~Ray() = default;

        rt::Vector3 &getPos() {return this->_position;}
        rt::Vector3 const& getPos() const {return this->_position;}
        rt::Vector3 &getDir() {return this->_direction;}
        rt::Vector3 const& getDir() const {return this->_direction;}
        void setPos(rt::Vector3 const& __pos) {this->_position = __pos;}
        void setDir(rt::Vector3 const& __dir) {this->_direction = __dir;}

        void raytrace(rt::Camera const&, sf::Vector2i const&);
        void computeCamera(rt::Camera const&);
        void compute(rt::AMesh const *);

    private:
        rt::Vector3 _position;
        rt::Vector3 _direction;
    };
}

#endif /* end of include guard: RAY_HPP_ */

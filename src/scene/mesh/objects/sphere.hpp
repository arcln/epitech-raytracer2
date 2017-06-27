//
// sphere.hpp for rt in /home/arthur/B2/MUL/raytracer2/src/mesh/objects/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr  5 16:28:59 2017 Arthur Chaloin
// Last update Sun May 28 00:28:23 2017 Paul Laffitte
//

#ifndef SPHERE_HPP_
# define SPHERE_HPP_

# include "mesh.hpp"

namespace rt
{
    class Sphere : public AMesh
    {
    public:
        Sphere() = default;
        Sphere(rt::Sphere const&) = default;
        rt::Sphere &operator =(rt::Sphere const&) = default;
        ~Sphere() = default;

        rt::Intersection    intersect(rt::Ray const&, rt::Scene const*) const;
        rt::Vector3         getNormal(rt::Vector3 const&, rt::Vector3 const&) const;

        void applyParameterOnVertices(std::vector<rt::Vector3> &vertices) const;
    };
}

#endif /* end of include guard: SPHERE_HPP_ */

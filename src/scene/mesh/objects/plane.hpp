//
// sphere.hpp for rt in /home/arthur/B2/MUL/raytracer2/src/mesh/objects/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr  5 16:28:59 2017 Arthur Chaloin
// Last update Sun May 28 00:28:16 2017 Paul Laffitte
//

#ifndef PLANE_HPP_
# define PLANE_HPP_

# include "mesh.hpp"

namespace rt
{
    class Plane : public AMesh
    {
    public:
        Plane() = default;
        Plane(rt::Plane const&) = default;
        rt::Plane &operator =(rt::Plane const&) = default;
        ~Plane() = default;

        rt::Intersection    intersect(rt::Ray const&, rt::Scene const*) const;
        rt::Vector3         getNormal(rt::Vector3 const&, rt::Vector3 const&) const;

        void applyParameterOnVertices(std::vector<rt::Vector3> &vertices) const;
    };
}

#endif /* end of include guard: PLANE_HPP_ */

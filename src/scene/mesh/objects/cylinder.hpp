//
// sphere.hpp for rt in /home/arthur/B2/MUL/raytracer2/src/mesh/objects/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr  5 16:28:59 2017 Arthur Chaloin
// Last update Sun May 28 00:28:08 2017 Paul Laffitte
//

#ifndef CYLINDER_HPP_
# define CYLINDER_HPP_

# include "mesh.hpp"

namespace rt
{
    class Cylinder : public AMesh
    {
    public:
        Cylinder() = default;
        Cylinder(rt::Cylinder const&) = default;
        rt::Cylinder &operator =(rt::Cylinder const&) = default;
        ~Cylinder() = default;

        rt::Intersection    intersect(rt::Ray const&, rt::Scene const*) const;
        rt::Vector3         getNormal(rt::Vector3 const&, rt::Vector3 const&) const;

        void applyParameterOnVertices(std::vector<rt::Vector3> &vertices) const;
    };
}

#endif /* end of include guard: CYLINDER_HPP_ */

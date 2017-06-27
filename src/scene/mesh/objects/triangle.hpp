//
// sphere.hpp for rt in /home/arthur/B2/MUL/raytracer2/src/mesh/objects/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr  5 16:28:59 2017 Arthur Chaloin
// Last update Sun May 28 00:28:29 2017 Paul Laffitte
//

#ifndef TRIANGLE_HPP_
# define TRIANGLE_HPP_

# include "mesh.hpp"

namespace rt
{
    class Triangle : public AMesh
    {
    public:
        Triangle() = default;
        Triangle(rt::Vector3 a, rt::Vector3 b, rt::Vector3 c) : AMesh() {top[0] = a; top[1] = b; top[2] = c;}
        Triangle(rt::Triangle const&) = default;
        rt::Triangle &operator =(rt::Triangle const&) = default;
        ~Triangle() = default;

        rt::Intersection    intersect(rt::Ray const&, rt::Scene const*) const;
        rt::Vector3         getNormal(rt::Vector3 const&, rt::Vector3 const&) const;


        void applyParameterOnVertices(std::vector<rt::Vector3> &vertices) const;

        rt::Vector3 top[3];
    };
}

#endif /* end of include guard: TRIANGLE_HPP_ */

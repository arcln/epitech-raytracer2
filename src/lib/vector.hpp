//
// vector.hpp for rt in /home/arthur/B2/MUL/raytracer2/src/lib/
//
// Made by John Doe
// Login   <login_x@epitech.eu>
//
// Started on  Fri Mar 24 10:55:45 2017 John Doe
// Last update Sat May 27 17:44:10 2017 Thomas ARBONA
//

#ifndef VECTOR_HPP_
# define VECTOR_HPP_

# include <string>

namespace rt
{
  class Matrix;
    class Vector3
    {
    public:
        float  x{0};
        float  y{0};
        float  z{0};

        Vector3() = default;
        Vector3(float x, float y = 0, float z = 0);
        ~Vector3() = default;

        float   len();
        void    normalize();
        void    multMatrix(rt::Matrix const&, int);
        float	getDist(Vector3 v);

        float    operator * (Vector3 const&) const;
        Vector3  operator * (float const&) const;
        Vector3  operator / (float const&) const;
        Vector3  operator +(Vector3 const&);
        Vector3  operator -(Vector3 const&);
        Vector3  cross(Vector3 const&);

        void print() const;
        void print(std::string const&) const;
    };
}

#endif /* end of include guard: VECTOR_HPP_ */

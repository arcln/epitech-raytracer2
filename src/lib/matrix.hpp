//
// matrix.hpp for rt in /home/arthur/B2/MUL/raytracer2/src/lib/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Thu Apr 13 12:59:11 2017 Arthur Chaloin
// Last update Fri May 26 18:55:56 2017 Arthur Chaloin
//

#ifndef MATRIX_HPP_
# define MATRIX_HPP_

# include <string>

namespace rt
{
  class Vector3;
    class Matrix
    {
    public:
        Matrix(){};
        Matrix(rt::Matrix const&) = default;
        rt::Matrix &operator =(rt::Matrix const&) = default;
        ~Matrix() = default;

        void init();
        auto operator [](int index) {return _data[index];}
        auto operator [](int index) const {return _data[index];}
        rt::Matrix operator *(rt::Matrix const&);
        rt::Matrix operator *(rt::Vector3 const&);
        void invert();

        void print() const;
        void print(std::string const&) const;

    private:
        float _data[4][4];
    };
}

#endif /* !MATRIX_HPP_ */

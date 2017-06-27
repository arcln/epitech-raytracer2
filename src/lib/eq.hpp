//
// eq.hpp for rt in /home/arthur/B2/MUL/raytracer2/src/lib/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr 12 16:54:28 2017 Arthur Chaloin
// Last update Wed May 24 16:59:11 2017 Arthur Chaloin
//

#ifndef EQ_HPP_
# define EQ_HPP_

# include "scene.hpp"

#ifndef MIN
# define MIN(x, y) ((x < y) ? x : y)
#endif

#ifndef MAX
# define MAX(x, y) ((x > y) ? x : y)
#endif

#ifndef SQUARE
# define SQUARE(x) (x * x)
#endif

namespace rt
{
    class Eq
    {
    public:
        Eq() = default;
        Eq(float a, float b = 0, float c = 0);
        ~Eq() = default;

        float solve(rt::Scene const *scene);

        void setA(float const __a) {_a = __a;};
        void setB(float const __b) {_b = __b;};
        void setC(float const __c) {_c = __c;};

    private:
        float _a;
        float _b;
        float _c;
    };
}

#endif /* end of include guard: EQ_HPP_ */

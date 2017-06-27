//
// camera.hpp for rt in /home/arthur/B2/MUL/raytracer2/src/scene/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr 12 20:23:51 2017 Arthur Chaloin
// Last update Sun May 28 15:28:25 2017 Paul Laffitte
//

#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# include "matrix.hpp"
# include "vector.hpp"

namespace rt
{
    class Camera
    {
    public:
        rt::Matrix matrix;
        float screen_dist;

        void addPosition(rt::Vector3 const& pos);
        void addRotation(rt::Vector3 rot);

        Vector3 const& getPosition() const {return _position;}
        Vector3 const& getLookAt() const {return _lookAt;}

    private:
        Vector3 _position{0.f, 0.f, 0.f};
        Vector3 _lookAt{0.f, 0.f, -1.f};
    };
}

#endif /* !CAMERA_HPP_ */

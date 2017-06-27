//
// mesh.hpp for rt in /home/arthur/B2/MUL/raytracer2/src/mesh/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr  5 15:09:17 2017 Arthur Chaloin
// Last update Sun May 28 15:25:51 2017 Arthur Chaloin
//

#ifndef MESH_HPP_
# define MESH_HPP_

# include "ray.hpp"
# include "vector.hpp"
# include "matrix.hpp"
# include "texture.hpp"

namespace rt
{
    class Scene;

    class AMesh
    {
    public:
        virtual ~AMesh() = default;

        rt::Matrix matrix;
        rt::Matrix invMatrix;

        virtual rt::Intersection   intersect(rt::Ray const&, rt::Scene const*) const = 0;
        virtual rt::Vector3        getNormal(rt::Vector3 const&, rt::Vector3 const& ray) const = 0;

        virtual void applyParameterOnVertices(std::vector<rt::Vector3> &vertices) const = 0;

        float getParam() const {return _param;}
        void setParam(float const& __param) {_param = __param;}

        void addPosition(rt::Vector3 const& pos);
        void addRotation(rt::Vector3 rot);

        float getReflectLevel() const {return _reflectLevel;}
        void setReflectLevel(float const& value) {_reflectLevel = value;}

        float getRefractIndice() const {return _refractIndice;}
        void setRefractIndice(float const& value) {_refractIndice = value;}

        sf::Color getColor() const {return _color;}
        void setColor(sf::Color const& __color) {_color = __color;}


        rt::TextureType getTexture() const {return _textureType;}
        void setTexture(rt::TextureType __type) {_textureType = __type;}

        float getBump() const {return _bump;}
        void setBump(float __bump) {_bump = __bump;}
        float getBumpScale() const {return _bumpScale;}
        void setBumpScale(float __bumpScale) {_bumpScale = __bumpScale;}
      rt::Vector3 computeBump(rt::Vector3 normal, rt::Vector3 const& hit) const;

    protected:
        AMesh() {matrix.init();}
        AMesh(rt::AMesh const&) = default;
        rt::AMesh& operator =(rt::AMesh const&) = default;

    private:
        float   _param{1};
        float   _reflectLevel{0};
        float   _refractIndice{0};
        float	_bump{0.};
        float	_bumpScale{10.};
        sf::Color _color{255, 255, 255, 255};
      rt::TextureType _textureType{rt::TextureType::None};
    };
}

#endif /* end of include guard: MESH_HPP_ */


//
// scene.hpp for rt in /home/arthur/B2/MUL/raytracer2/src/scene/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr  5 17:03:17 2017 Arthur Chaloin
// Last update Tue Jun  6 00:29:06 2017 Arthur Chaloin
//

#ifndef SCENE_HPP_
# define SCENE_HPP_

# include <vector>
# include <string>
# include <SFML/Graphics.hpp>
# include "objects/triangle.hpp"
# include "camera.hpp"
# include "light.hpp"

# define MACOS

#ifndef WIDTH
# define WIDTH 1000
#endif

#ifndef HEIGHT
# define HEIGHT 1000
#endif

#ifndef BIN_PATH
# define BIN_PATH "../bin/raytracer"
#endif

#ifndef SMOOTH_LEVEL
# define SMOOTH_LEVEL 10
#endif

#ifndef SMOOTH_POWER
# define SMOOTH_POWER 10.f
#endif

namespace rt
{
    class Scene
    {
    public:
        Scene(){};
        ~Scene(){};

        void init();
        void reset();

        void compute();
        void render();
        void putPixel(sf::Vector2i const&, sf::Color const&);
        float getInterDist(rt::Ray &base) const;

        float getEpsilon() const {return _epsilon;}
        void  setEpsilon(float const& __epsilon) {_epsilon = __epsilon;}

        rt::Camera &getCamera() {return _camera;}
        rt::Camera const& getCamera() const {return _camera;}
        std::vector<rt::AMesh *> &getObjs() {return _objects;}
        std::vector<rt::AMesh *> const& getObjs() const {return _objects;}
        std::vector<rt::Vector3> &getVertices() {return _vertices;}
        std::vector<rt::Vector3> const& getVertices() const {return _vertices;}
        std::vector<rt::Vector3> &getColors() {return _colors;}
        std::vector<rt::Vector3> const& getColors() const {return _colors;}
        std::vector<rt::Light *> &getLights() {return _lights;}
        std::vector<rt::Light *> const& getLights() const {return _lights;}
        sf::Uint8 *getPixels() const {return _pixels;}

        void remote(bool __value) {_network = __value;}
        void isClient(bool __value) {_isClient = __value;}
        bool client() const {return _isClient;}
        int getThreadNb() const {return _threadNb;}
        void setThreadNb(int const nb) {_threadNb = nb;}

    private:
        bool _network, _isClient;
        float _epsilon = 0.01;
        int _threadNb = 1;
        std::vector<rt::AMesh *> _objects;
        std::vector<rt::Vector3> _vertices;
        std::vector<rt::Vector3> _colors;
        std::vector<rt::Light *> _lights;
        rt::Camera _camera;

        sf::Uint8 *_pixels;
    };
}

#endif /* end of include guard: SCENE_HPP_ */

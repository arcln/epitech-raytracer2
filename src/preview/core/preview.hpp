//
// preview.hpp for raytracer2 in /home/onehandedpenguin/Dev/CGP_2016/raytracer2/src/preview/core/
//
// Made by Paul Laffitte
// Login   <paul.laffitte@epitech.eu>
//
// Started on  Thu May 25 16:23:36 2017 Paul Laffitte
// Last update Sun May 28 18:00:57 2017 Paul Laffitte
//

#ifndef DOOM_HPP_
# define DOOM_HPP_

# include <cmath>
# include "video.hpp"
# include "scene.hpp"
# include "parser.hpp"
# include "objects/triangle.hpp"

class Preview
{
public:
    Preview(){}
    ~Preview(){}

    void init(Video &video, rt::Scene &scene);
    void start(Video &video, rt::Parser &parser);
    void turn(Video &video);
    void poll(Video &video);

    void setPlaying(bool __value) {_playing = __value;}
    bool isPlaying() const {return _playing;}
    char **_envp;

private:
    bool _playing;
    bool _initMouse = true;
    bool _handleControls = true;
    bool _freeCamera;
    unsigned int _handleControlsTmp = 50;
    rt::Scene _scene;
    const char *_scenePath;
    rt::Vector3 _position = rt::Vector3(0.f, 0.f, 15.f);
    sf::Vector2f _rotation = sf::Vector2f(M_PI, 0.f);
    rt::Vector3 _lookAt = rt::Vector3(0.f, 0.f, -1.f);
    rt::Vector3 _up = rt::Vector3(0.f, 1.f, 0.f);
};

#endif /* end of include guard: DOOM_HPP_ */

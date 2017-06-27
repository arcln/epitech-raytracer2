//
// video.hpp for raytracer2 in /home/onehandedpenguin/Dev/CGP_2016/raytracer2/src/preview/core/
//
// Made by Paul Laffitte
// Login   <paul.laffitte@epitech.eu>
//
// Started on  Thu May 25 16:24:26 2017 Paul Laffitte
// Last update Sat May 27 23:18:11 2017 Paul Laffitte
//

#ifndef VIDEO_HPP_
# define VIDEO_HPP_

# include <vector>
# include <GLFW/glfw3.h>
# include "vector.hpp"
# include "scene.hpp"

class Video
{
public:
    Video(){}
    ~Video(){}

    void init();
    void draw(rt::Matrix mvp, rt::Scene const& scene);
    void update();
    void clear();

    void bindObj(std::vector<rt::Vector3> &vertices, std::vector<rt::Vector3> &colors);

    GLFWwindow *getWindow() {return _window;}

private:
    void errorShader(GLuint shaderId);
    void errorGlProgram(GLuint programId);
    GLuint loadShader(std::string const& filename, GLuint shaderId);
    GLuint loadGlProgram(std::string const& vertexFile, std::string const& fragmentFile);

    GLFWwindow *_window;
    GLuint _program;
    GLuint _vertexShader;
    GLuint _fragmentShader;
    GLuint _matrixID;

    int _nbVertices;
    GLuint _vertexId;
    GLuint _vertexArray;
    int _nbColors;
    GLuint _colorId;
    GLuint _colorArray;
};

#endif /* end of include guard: VIDEO_HPP_ */

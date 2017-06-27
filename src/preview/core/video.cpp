//
// video.cpp for raytracer2 in /home/onehandedpenguin/Dev/CGP_2016/raytracer2/src/preview/core/
//
// Made by Paul Laffitte
// Login   <paul.laffitte@epitech.eu>
//
// Started on  Thu May 25 16:25:04 2017 Paul Laffitte
// Last update Sun May 28 15:00:04 2017 Paul Laffitte
//

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "video.hpp"
#include "matrix.hpp"

void Video::errorShader(GLuint shaderId)
{
    GLint result;
    int errorLen;
    char *message;

    result = GL_FALSE;
    errorLen = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &errorLen);
    if (errorLen > 1 && (message = static_cast<char*>(malloc(sizeof(char) * (errorLen + 1))))) {
        glGetShaderInfoLog(shaderId, errorLen, NULL, message);
        std::cerr << message << std::endl;
        free(message);
    }
    else if (errorLen > 1) {
        std::cerr << "Shaders: An error occured with a shader\n" << std::endl;
    }
}

void Video::errorGlProgram(GLuint programId)
{
    GLint result;
    int errorLen;
    char *message;

    result = GL_FALSE;
    errorLen = 0;
    glGetShaderiv(programId, GL_LINK_STATUS, &result);
    glGetShaderiv(programId, GL_INFO_LOG_LENGTH, &errorLen);
    if (errorLen > 1 && (message = static_cast<char*>(malloc(sizeof(char) * (errorLen + 1))))) {
        glGetShaderInfoLog(programId, errorLen, NULL, message);
        std::cerr << message << std::endl;
        free(message);
    }
    else if (errorLen > 1) {
        std::cerr << "Shaders: An error occured with a program\n" << std::endl;
    }
}

GLuint Video::loadShader(std::string const& filename, GLuint shaderId)
{
    std::string line;
    std::string file;
    std::ifstream shaderFile(filename);

    file = "";
    if (shaderFile.is_open()) {
        while (getline(shaderFile, line)) {
            file += line + '\n';
        }
        shaderFile.close();
    }

    const GLchar* source = strdup(file.c_str());
    glShaderSource(shaderId, 1, static_cast<const GLchar**>(&source), NULL);
    glCompileShader(shaderId);
    errorShader(shaderId);
    return (0);
}

GLuint Video::loadGlProgram(std::string const& vertexFile, std::string const& fragmentFile)
{
    GLuint	programId;
    GLuint	vertexId;
    GLuint	fragmentId;

    vertexId = glCreateShader(GL_VERTEX_SHADER);
    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    programId = glCreateProgram();
    if (loadShader(vertexFile, vertexId) == 84) {
        std::cerr << "Could not read the vertex shader '" << vertexFile << "'" << std::endl;
    }
    if (loadShader(fragmentFile, fragmentId) == 84) {
        std::cerr << "Could not read the fragment shader '" << fragmentFile << "'" << std::endl;
    }
    glAttachShader(programId, vertexId);
    glAttachShader(programId, fragmentId);
    glLinkProgram(programId);
    errorGlProgram(programId);
    glDetachShader(programId, vertexId);
    glDetachShader(programId, fragmentId);
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
    return (programId);
}

void Video::init()
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to init GLFW.");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    _window = glfwCreateWindow(1280, 720, "Preview", NULL, NULL);
    if (!_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to open window.");
    }

    glfwMakeContextCurrent(_window);
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to init glew.");
    }

    _program = loadGlProgram("../shaders/simple.vert", "../shaders/simple.frag");

    _matrixID = glGetUniformLocation(_program, "MVP");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
}

void Video::bindObj(std::vector<rt::Vector3> &vertices, std::vector<rt::Vector3> &colors)
{
    _nbVertices = vertices.size();
    _nbColors = colors.size();

    // VAO creation
    glGenVertexArrays(1, &_vertexId);
    glBindVertexArray(_vertexId);

    // Vextex buffer creation
    glGenBuffers(1, &_vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexArray);

    // Color buffer creation
    glGenBuffers(1, &_colorArray);
    glBindBuffer(GL_ARRAY_BUFFER, _colorArray);
}

void Video::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Video::draw(rt::Matrix mvp, rt::Scene const& scene)
{
    glUseProgram(_program);
    glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &mvp[0][0]);

    // Enable the vertex buffer
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexArray);
    glBufferData(GL_ARRAY_BUFFER, _nbVertices * sizeof(rt::Vector3), &scene.getVertices()[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Enable the color buffer
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _colorArray);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBufferData(GL_ARRAY_BUFFER, _nbColors * sizeof(rt::Vector3), &scene.getColors()[0], GL_STATIC_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, 3 * _nbVertices);

    // Disable buffers after using thems
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Video::update()
{
    glfwSwapBuffers(_window);
}

//
// preview.cpp for raytracer2 in /home/onehandedpenguin/Dev/CGP_2016/raytracer2/src/preview/core/
//
// Made by Paul Laffitte
// Login   <paul.laffitte@epitech.eu>
//
// Started on  Thu May 25 16:24:48 2017 Paul Laffitte
// Last update Sun May 28 18:50:41 2017 Paul Laffitte
//

#include <iostream>
#include <string.h>
#include <math.h>
#include "preview.hpp"
#include "parser.hpp"

void Preview::init(Video &video, rt::Scene &scene)
{
    video.bindObj(scene.getVertices(), scene.getColors());
    _scene = scene;
}

void Preview::start(Video &video, rt::Parser &parser)
{
    setPlaying(true);

    _scenePath = parser.getPath().c_str();
    int i = 0;
    while (isPlaying()) {
        parser.refresh(_scene);
        turn(video);
        video.update();
        poll(video);
        ++i;
    }
}

void Preview::turn(Video &video)
{
    // Projection matrix
    rt::Matrix projection;
    float ar = 1920.0f / 1080.0f;
    float zNear = 0.1f;
    float zFar = 1000.0f;
    float zRange = zFar - zNear;
    float fov = 70.f * M_PI / 180.0f;

    projection.init();
    projection[0][0] = 1 / (ar * tanf(fov / 2));
    projection[1][1] = 1 / tanf(fov / 2);
    projection[2][2] = -((zFar + zNear) / zRange);
    projection[2][3] = -1;
    projection[3][2] = -((2 * zFar * zNear) / zRange);
    projection[0][0] = 1 / (ar * tan(fov / 2));
    projection[1][1] = 1 / tanf(fov / 2);

    // View matrix
    rt::Matrix view;

    rt::Vector3 position, lookAt;
    if (_freeCamera) {
        position = _position;
        lookAt = _lookAt;
    } else {
        position = _scene.getCamera().getPosition();
        lookAt = _scene.getCamera().getLookAt();
    }

    lookAt = lookAt + position;
    rt::Vector3 zAxis = position - lookAt;
    zAxis.normalize();
    rt::Vector3 xAxis = _up.cross(zAxis);
    xAxis.normalize();
    rt::Vector3 yAxis = zAxis.cross(xAxis);

    view[0][0] = xAxis.x;
    view[1][0] = xAxis.y;
    view[2][0] = xAxis.z;
    view[3][0] = -(xAxis * position);
    view[0][1] = yAxis.x;
    view[1][1] = yAxis.y;
    view[2][1] = yAxis.z;
    view[3][1] = -(yAxis * position);
    view[0][2] = zAxis.x;
    view[1][2] = zAxis.y;
    view[2][2] = zAxis.z;
    view[3][2] = -(zAxis * position);
    view[0][3] = 0;
    view[1][3] = 0;
    view[2][3] = 0;
    view[3][3] = 1;

    // Model matrix
    rt::Matrix model;
    model.init();

    // MVP matrix
    rt::Matrix mvp = model * view * projection;

    // Draw
    video.clear();
    video.draw(mvp, _scene);
}

void Preview::poll(Video &video)
{
    glfwPollEvents();
    if (glfwGetKey(video.getWindow(), GLFW_KEY_DELETE) == GLFW_PRESS
    || glfwWindowShouldClose(video.getWindow())) {
        setPlaying(false);
    }

    if (_handleControlsTmp > 20 && glfwGetKey(video.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        _handleControls = !_handleControls;
        _handleControlsTmp = 0;
    }
    ++_handleControlsTmp;

    if (!_handleControls) {
        return;
    }

    _freeCamera = !(glfwGetKey(video.getWindow(), GLFW_KEY_V) == GLFW_PRESS);
    if (glfwGetKey(video.getWindow(), GLFW_KEY_B) == GLFW_PRESS) {
        system("clear");
        std::cout << "Camera position: " << _position.x << " " << _position.y << " " << _position.z << std::endl;
        std::cout << "Camera rotation: " << atan(_lookAt.y / _lookAt.x) * 180 / M_PI << " " << acos(_lookAt.z) * 180 / M_PI << " " << 0 << std::endl;
        std::cout << "Vertices: " << _scene.getVertices().size() << std::endl;
        std::cout << "Lights: " << _scene.getLights().size() << std::endl;
        std::cout << "Threads: " << _scene.getThreadNb() << std::endl;
        std::cout << "Epsilon: " << _scene.getEpsilon() << std::endl;
        std::cout << "Version: 1.0.0 (Keynote)" << std::endl;
        std::cout << "Version name: Keynote" << std::endl;
    }

    if (glfwGetKey(video.getWindow(), GLFW_KEY_R) == GLFW_PRESS) {
        char* const argv[5]{strdup("./raytracer2"), strdup(_scenePath), strdup("-t"), strdup("4"), nullptr};
        if (execve("./raytracer2", argv, _envp) == -1) {
            std::cerr << "Unable to start a render..." << std::endl;
        }
    }

    float mouseSpeed = 0.01;
	double mouse_x, mouse_y;
    if (_initMouse == true) {
        glfwSetCursorPos(video.getWindow(), 1280 / 2, 720 / 2);
        _initMouse = false;
    }
	glfwGetCursorPos(video.getWindow(), &mouse_x, &mouse_y);
	glfwSetCursorPos(video.getWindow(), 1280 / 2, 720 / 2);
	_rotation.x += float(mouseSpeed * (1280.f / 2.f - mouse_x)) * 1.5;
    _rotation.y += float(mouseSpeed * (720.f / 2.f - mouse_y));
    if (_rotation.y > M_PI / 2 - (M_PI / 100)) {
        _rotation.y = M_PI / 2 - (M_PI / 100);
    } else if (_rotation.y < - M_PI / 2 + (M_PI / 100)) {
        _rotation.y = - M_PI / 2 + (M_PI / 100);
    }
    _lookAt = rt::Vector3(cos(_rotation.y) * sin(_rotation.x), sin(_rotation.y), cos(_rotation.y) * cos(_rotation.x));

    float moveSpeed = 0.5;
    if (glfwGetKey(video.getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        moveSpeed *= 3;
    }
    rt::Vector3 vectorSpeed = _lookAt * moveSpeed;
    if (glfwGetKey(video.getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
        _position = _position + vectorSpeed;
    }
    if (glfwGetKey(video.getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
        _position = _position - vectorSpeed;
    }
    rt::Vector3 horizontal(_lookAt.x, _lookAt.y, _lookAt.z);
    float rotation_x = _rotation.x - M_PI / 2;
    horizontal = rt::Vector3(cos(_rotation.y) * sin(rotation_x), sin(_rotation.y), cos(_rotation.y) * cos(rotation_x));
    vectorSpeed = horizontal * moveSpeed;
    if (glfwGetKey(video.getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
        _position = _position - vectorSpeed;
    }
    if (glfwGetKey(video.getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
        _position = _position + vectorSpeed;
    }
    if (glfwGetKey(video.getWindow(), GLFW_KEY_C) == GLFW_PRESS) {
        _position.y -= moveSpeed;
    }
    if (glfwGetKey(video.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        _position.y += moveSpeed;
    }
}

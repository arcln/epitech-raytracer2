//
// main.cpp for raytracer2 in /home/onehandedpenguin/Dev/CGP_2016/raytracer2/src/preview/
//
// Made by Paul Laffitte
// Login   <paul.laffitte@epitech.eu>
//
// Started on  Thu May 25 16:25:24 2017 Paul Laffitte
// Last update Sun May 28 18:01:24 2017 Paul Laffitte
//

#include <iostream>
#include <string>
#include <exception>
#include "core/preview.hpp"
#include "core/video.hpp"
#include "scene.hpp"
#include "parser.hpp"

int main(int argc, char **argv, char **envp)
{
    if (argc != 2) {
        std::cerr << "Usage: ./raytracer2_preview scene" << std::endl;
        return 84;
    }

    rt::Scene  scene;
    rt::Parser parser;

    scene.remote(false);
    scene.isClient(false);
    try {
        scene.init();
        parser.loadFromFile(scene, argv[1]);
    }
    catch (std::runtime_error e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }


    Preview core;
    Video video;

    try {
        video.init();
        core.init(video, scene);
        core._envp = envp;
        core.start(video, parser);
    }
    catch (std::runtime_error e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

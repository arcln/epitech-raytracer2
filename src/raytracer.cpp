//
// raytracer.cpp for rt in /home/arthur/B2/MUL/raytracer2/src/
//
// Made by John Doe
// Login   <login_x@epitech.eu>
//
// Started on  Fri Mar 24 10:25:09 2017 John Doe
// Last update Sun May 28 15:36:45 2017 Arthur Chaloin
//
#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>
#include <time.h>
#include "scene.hpp"
#include "parser.hpp"
#include "mesh.hpp"
#include "objects/sphere.hpp"
#include "perlin.hpp"

int main(const int ac, char *av[])
{
    if (ac < 2) {
        std::cerr << "Usage: " << av[0] << " <scene.rt>" << std::endl
                  << "\t-t <threads nb> -- Specify the number of threads for rendering" << std::endl;
        return 1;
    }
    srand(time(NULL));

    char c;
    rt::Scene  scene;
    rt::Parser parser;

    scene.remote(false);
    scene.isClient(false);
    while ((c = getopt(ac, av, "cnt:")) != -1) {
        switch (c) {
            case 'c': scene.isClient(true);
                break;
            case 'n': scene.remote(true);
                break;
            case 't':
                scene.setThreadNb(std::atoi(optarg));
                break;
        }
    }

    try {
        scene.init();
        parser.loadFromFile(scene, av[ac - 1]);
    } catch (std::runtime_error e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    if (!scene.client()) {
        std::thread renderThread(&rt::Scene::compute, scene);
        renderThread.detach();
        scene.render();
    } else {
        scene.compute();
    }

    return 0;
}

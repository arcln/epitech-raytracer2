//
// scene.cpp for rt in /home/arthur/B2/MUL/raytracer2/src/scene/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Wed Apr  5 17:09:21 2017 Arthur Chaloin
// Last update Tue Jun  6 00:05:39 2017 Arthur Chaloin
//
#include <iostream>
#include <thread>
#include <cstring>
#include <climits>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "scene.hpp"
#include "pixel.hpp"
#include "client.hpp"

void rt::Scene::init()
{
    _pixels = (sf::Uint8 *)malloc(sizeof(sf::Uint8) * (WIDTH * HEIGHT * 4));
    if (!_pixels) {
        throw std::runtime_error("Error: Can't perform malloc.");
    }
    reset();
}

void rt::Scene::reset()
{
    _objects.clear();
    _vertices.clear();
    _colors.clear();
    _lights.clear();
    memset(_pixels, 0, WIDTH * HEIGHT * 4);
}

void rt::Scene::render()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "raytracer");
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Event event;

    texture.create(WIDTH, HEIGHT);
    texture.setSmooth(true);
    sprite.setTexture(texture);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Key::Escape)) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::S) {
                texture.copyToImage().saveToFile("../screens/screen_" + std::to_string(time(NULL)) + ".png");
            }
        }
        texture.update(_pixels);
        window.clear();
        window.draw(sprite);
        window.display();
    }
}

void rt::Scene::putPixel(sf::Vector2i const& pos, sf::Color const& color)
{
    if (pos.y >= 0 && pos.y < HEIGHT && pos.x >= 0 && pos.x < WIDTH) {
        if (!_pixels[(pos.y * WIDTH + pos .x) * 4 + 3]) {
            _pixels[(pos.y * WIDTH + pos .x) * 4] = color.r;
            _pixels[(pos.y * WIDTH + pos .x) * 4 + 1] = color.g;
            _pixels[(pos.y * WIDTH + pos .x) * 4 + 2] = color.b;
            _pixels[(pos.y * WIDTH + pos .x) * 4 + 3] = color.a;
        } else {
            _pixels[(pos.y * WIDTH + pos .x) * 4] = (color.r / 2) + _pixels[(pos.y * WIDTH + pos .x) * 4] / 2;
            _pixels[(pos.y * WIDTH + pos .x) * 4 + 1] = (color.g / 2) + _pixels[(pos.y * WIDTH + pos .x) * 4 + 1] / 2;
            _pixels[(pos.y * WIDTH + pos .x) * 4 + 2] = (color.b / 2) + _pixels[(pos.y * WIDTH + pos .x) * 4 + 2] / 2;
            _pixels[(pos.y * WIDTH + pos .x) * 4 + 3] = (color.a / 2) + _pixels[(pos.y * WIDTH + pos .x) * 4 + 3] / 2;
        }
    }
}

float rt::Scene::getInterDist(rt::Ray &base) const
{
  rt::Intersection inter, min;
  rt::Ray ray;

  min.distance = INT_MAX;
  std::vector<AMesh *> objs = this->getObjs();
  for (auto it = objs.begin(); it != objs.end(); ++it) {
    ray = base;
    ray.compute(*it);
    inter = (*it)->intersect(ray, this);

    if (inter.distance != -1 && inter.distance < min.distance) {
      min.distance = inter.distance;
      min.hit = inter.hit;
    }
  }

  return (min.distance != INT_MAX) ? min.distance : -1.;
}

void rt::Scene::compute()
{
    sf::Vector2i cursor(-1, -1);
    rt::net::Client client;

    if (_isClient) {
        try {
            client.init();
            client.link(_network);

            while (1) {
                try {
                    client.compute(*this);
                }
                catch (std::string error) {
                    std::cerr << error << std::endl;
                    return;
                }
            }
        }
        catch (std::string error) {
            std::cerr << error << std::endl;
            exit(1);
        }
    } else {
        if (_network) {
            try {
                client.init();
                client.link(_network);
                client.lead(*this);
            }
            catch (std::string error) {
                std::cerr << error << std::endl;
                exit(1);
            }
        } else {
            std::vector<std::thread> threads;

            for (int i = 0; i < this->_threadNb; i++) {
                sf::Vector2i start(0, ((float)i / (float)this->_threadNb) * (float)HEIGHT);
                sf::Vector2i end(0, ((float)(i + 1) / (float)this->_threadNb) * (float)HEIGHT);

                threads.push_back(std::thread([this, start, end](){
                    rt::Pixel pixel;

                    while ("We love raytracer it's a great project") {
                        sf::Vector2i cursor(start.x, start.y);

                        while (++cursor.y <= end.y) {
                            cursor.x = -1;
                            while (++cursor.x < WIDTH) {
                                pixel.compute(*this, cursor);
                                this->putPixel(cursor, pixel.getColor());
                            }
                        }
                    }
                }));
            }
            threads.back().join();
        }
    }
}

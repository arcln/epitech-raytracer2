//
// network.cpp for test in /home/arthur/Documents/network_test/src/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Fri Apr 14 15:49:41 2017 Arthur Chaloin
// Last update Thu Apr 20 17:44:54 2017 Arthur Chaloin
//
#include <iostream>
#include <string>
#include <thread>
#include <cstring>
#include "client.hpp"
#include "pixel.hpp"

int rt::net::Client::_sd;
bool filling = true;

void rt::net::Client::init()
{
    _sd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sd < 0) {
        throw std::runtime_error("Failed to create socket.");
    }
    // _server.sin_addr.s_addr = inet_addr("51.254.112.135");
    // _server.sin_addr.s_addr = inet_addr("10.101.53.174");
    _server.sin_addr.s_addr = inet_addr("127.0.0.1");
    _server.sin_family = AF_INET;
    _server.sin_port = htons(8888);
}

void rt::net::Client::link(bool master)
{
    char msg[PKG_SIZE];

    memset(msg, 0, PKG_SIZE);
    if (connect(_sd, (struct sockaddr *)&_server, sizeof(_server)) < 0) {
        throw std::runtime_error("Failed to connect !");
    } else {
        if (master) {
            msg[0] = 1;
        } else {
            msg[0] = 0;
        }
        if (send(_sd, msg, PKG_SIZE, 0) < 0) {
            throw std::runtime_error("Failed to send.");
        } else {
            std::cout << "Connected successfully." << std::endl;
        }
    }
}

void rt::net::Client::_filler(rt::Scene& scene)
{
    int bytes;
    rt::net::Package pkg;

    while (filling) {
        if ((bytes = recv(_sd, &pkg, sizeof(rt::net::Package), 0)) < 0) {
            std::cerr << "Receive error." << std::endl;
            return;
        } else if (bytes == 0) {
            std::cerr << "Server disconnected." << std::endl;
            return;
        } else if (bytes != sizeof(rt::net::Package)) {
            continue;
        } else {
            for (auto index = 0; index < PKG_SIZE; index++) {
                if (filling && index + pkg.start >= 0 && index + pkg.start < WIDTH * HEIGHT * 4) {
                    scene.getPixels()[index + pkg.start] = pkg.data[index];
                }
            }
        }
    }
}

void rt::net::Client::lead(rt::Scene& scene)
{
    bool complete = false;
    char msg[PKG_SIZE];
    rt::net::Zone zone;

    std::thread filler(_filler, std::ref(scene));
    filler.detach();
    memset(msg, 0, PKG_SIZE);
    do {
        complete = true;
        for (auto index = 0; index < WIDTH * HEIGHT * 4; index += PKG_SIZE) {
            if (!scene.getPixels()[index + 3]) {
                complete = false;
                zone.start = index;
                zone.size = PKG_SIZE;
                memcpy(msg, &zone, sizeof(rt::net::Zone));
                if (send(_sd, msg, PKG_SIZE, 0) < 0) {
                    throw std::runtime_error("Failed to send.");
                }
            }
        }
    } while (!complete);
    filling = false;
    memset(msg, 1, PKG_SIZE);
    if (send(_sd, msg, PKG_SIZE, 0) < 0) {
        throw std::runtime_error("Failed to send stop signal.");
    }
}

void rt::net::Client::compute(rt::Scene& scene)
{
    int bytes;
    char message[PKG_SIZE];
    rt::net::Zone zone;
    rt::Pixel pixel;

    if ((bytes = recv(_sd, message, PKG_SIZE, 0)) < 0) {
        throw std::runtime_error("Failed to receive.");
    } else {
        zone = *((rt::net::Zone *)message);

        std::cout << "asked " << zone.start << '\n';
        for (auto index = zone.start; index < zone.start + zone.size; index += 4) {
            sf::Vector2i cursor((index / 4) % WIDTH, (index / 4) / WIDTH);
            pixel.compute(scene, cursor);
            scene.putPixel(cursor, pixel.getColor());
        }

        std::cout << "sending " << zone.start << '\n';
        if (send(_sd, scene.getPixels() + zone.start, zone.size, 0) < 0) {
            throw std::runtime_error("Failed to send.");
        }
    }
}

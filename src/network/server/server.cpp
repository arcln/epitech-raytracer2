//
// server.cpp for test in /home/arthur/Documents/network_test/src/server/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Fri Apr 14 17:27:37 2017 Arthur Chaloin
// Last update Thu Apr 20 17:47:24 2017 Arthur Chaloin
//
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include "server.hpp"

std::mutex dataM;
std::mutex masterM;

std::vector<Package> masterData;
std::vector<Package> data;

bool master = true;

void Server::start()
{
    int size = sizeof(struct sockaddr_in), new_socket, bytes;
    unsigned int id;
    char message[PKG_SIZE], stop[PKG_SIZE];
    Package pkg;

    _sd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sd < 0) {
        throw std::runtime_error("Failed to create socket.");
    }
    _server.sin_addr.s_addr = INADDR_ANY;
    _server.sin_family = AF_INET;
    _server.sin_port = htons(8888);

    if (bind(_sd, (struct sockaddr *)&_server , sizeof(_server)) < 0) {
        throw std::runtime_error("Failed binding socket.");
    } else {
        _printTime();
        std::cout << "Binding succes." << std::endl;
    }

    listen(_sd, 3);

    while (1) {
        if ((new_socket = accept(_sd, NULL, (socklen_t *)&size)) < 0) {
            throw std::runtime_error("Failed to accept connection.");
        } else {
            memset(message, 0, PKG_SIZE);
            if ((bytes = recv(new_socket, message, PKG_SIZE, 0)) < 0) {
                throw std::runtime_error("Failed to receive.");
            } else {
                if (message[0] == 1) {
                    masterData.clear();
                    master = true;
                    std::thread master(_master, new_socket);
                    master.detach();
                    _printTime();
                    std::cout << "Master connected." << std::endl;
                } else {
                    memset(stop, 1, PKG_SIZE);
                    dataM.lock();
                    id = 0;

                    for (auto it = data.begin(); it != data.end(); ++it) {
                        if (!memcmp(it->data, stop, PKG_SIZE)) {
                            memset(it->data, 0, PKG_SIZE);
                            std::thread client(_interface, new_socket, id);
                            client.detach();
                            _printTime();
                            std::cout << "Client " << id << " connected successfully." << '\n';
                            _printTime();
                            std::cout << "There is now " << _countClients() << " clients available." << '\n';
                            break;
                        }
                        id++;
                    }
                    if (id == data.size()) {
                        memset(pkg.data, 0, PKG_SIZE);
                        data.push_back(pkg);
                        std::thread client(_interface, new_socket, id);
                        client.detach();
                        _printTime();
                        std::cout << "Client " << id << " connected successfully." << '\n';
                        _printTime();
                        std::cout << "There is now " << _countClients() << " clients available." << '\n';
                    }
                    dataM.unlock();
                }
            }
        }
    }
}

void Server::_masterResponse(int sd)
{
    while (master) {
        masterM.lock();
        if (masterData.begin() != masterData.end()) {
            if (send(sd, masterData.back().data, sizeof(Package), 0) < 0) {
                _printTime();
                std::cerr << "Send failure." << std::endl;
            }
            masterData.pop_back();
        }
        masterM.unlock();
    }
}

void Server::_master(int sd)
{
    int bytes;
    char raw[PKG_SIZE], clean[PKG_SIZE], stop[PKG_SIZE];

    memset(clean, 0, PKG_SIZE);
    memset(stop, 1, PKG_SIZE);
    std::thread response(_masterResponse, sd);
    response.detach();
    while (1) {
        if ((bytes = recv(sd, raw, PKG_SIZE, 0)) < 0) {
            _printTime();
            std::cerr << "Receive error." << std::endl;
            master = false;
            return;
        } else if (bytes == 0) {
            _printTime();
            std::cerr << "Master disconnected." << std::endl;
            master = false;
            return;
        } else {
            if (!memcmp(raw, stop, PKG_SIZE)) {
                memset(&data[0], 0, data.size() * sizeof(Package));
            } else {
                bool set = false;

                do {
                    dataM.lock();
                    for (auto it = data.begin(); it != data.end(); ++it) {
                        if (!memcmp(it->data, clean, PKG_SIZE)) {
                            memcpy(it->data, raw, PKG_SIZE);
                            set = true;
                            break;
                        }
                    }
                    dataM.unlock();
                } while (!set);
            }
        }
    }
}

void Server::_interface(int sd, int id)
{
    int bytes;
    char raw[PKG_SIZE], clean[PKG_SIZE];
    Package pkg;

    memset(clean, 0, PKG_SIZE);
    while (1) {
        int wait = 1;

        while (wait) {
            dataM.lock();
            wait = !memcmp(data[id].data, clean, PKG_SIZE);
            dataM.unlock();
        }

        dataM.lock();
        if (send(sd, data[id].data, PKG_SIZE, 0) < 0) {
            dataM.unlock();
            return;
        } else {
            dataM.unlock();
            if ((bytes = recv(sd, raw, PKG_SIZE, 0)) < 0) {
                _printTime();
                std::cerr << "Receive error." << std::endl;
                return;
            } else if (bytes == 0) {
                memset(data[id].data, 1, PKG_SIZE);
                _printTime();
                std::cerr << "Client disconnected." << std::endl;
                return;
            } else {
                memcpy(pkg.data, raw, PKG_SIZE);
                pkg.start = *((int *)(data[id].data));
                masterM.lock();
                masterData.push_back(pkg);
                masterM.unlock();
                dataM.lock();
                memset(data[id].data, 0, PKG_SIZE);
                dataM.unlock();
            }
        }
    }
}

void Server::_printTime()
{
    time_t raw = time(NULL);
    char *format = ctime(&raw);
    format[19] = 0;
    std::cout << "[" << format << "] ";
}

int Server::_countClients()
{
    int count = 0;
    char stop[PKG_SIZE];

    memset(stop, 1, PKG_SIZE);
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (memcmp(it->data, stop, PKG_SIZE)) {
            count++;
        }
    }
    return count;
}

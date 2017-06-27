//
// main.cpp for test in /home/arthur/Documents/network_test/src/server/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Fri Apr 14 17:30:26 2017 Arthur Chaloin
// Last update Wed Apr 19 23:30:46 2017 Arthur Chaloin
//
#include <iostream>
#include <csignal>
#include "server.hpp"

int main()
{
    Server server;

    signal(SIGPIPE, SIG_IGN);
    try {
        server.start();
    }
    catch (std::string error) {
        std::cerr << error << std::endl;
    }

    return 0;
}

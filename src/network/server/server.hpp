//
// server.hpp for test in /home/arthur/Documents/network_test/src/server/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Fri Apr 14 17:24:18 2017 Arthur Chaloin
// Last update Thu Apr 20 17:52:47 2017 Arthur Chaloin
//

#ifndef SERVER_HPP_
# define SERVER_HPP_

# include <cstdio>
# include <sys/socket.h>
# include <arpa/inet.h>

# define PKG_SIZE   16000

struct Package {
    char data[PKG_SIZE];
    int start;
};

class Server
{
public:
    Server() = default;
    ~Server() = default;

    void start();

private:
    int _sd;
    struct sockaddr_in _server;

    static void _interface(int, int);
    static void _master(int);
    static void _masterResponse(int);
    static void _printTime();

    int _countClients();
};

#endif /* end of include guard: SERVER_HPP_ */

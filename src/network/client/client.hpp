//
// network.hpp for test in /home/arthur/Documents/network_test/src/
//
// Made by Arthur Chaloin
// Login   <arthur.chaloin@epitech.eu>
//
// Started on  Fri Apr 14 15:40:18 2017 Arthur Chaloin
// Last update Thu Apr 20 17:50:29 2017 Arthur Chaloin
//

#ifndef NETWORK_HPP_
# define NETWORK_HPP_

# include <cstdio>
# include <sys/socket.h>
# include <arpa/inet.h>
# include "scene.hpp"

# define PKG_SIZE   16000

namespace rt
{
    namespace net
    {
        struct Zone {
            int start;
            int size;
        };

        struct Package {
            char data[PKG_SIZE];
            int start;
        };

        class Client
        {
        public:
            Client() = default;
            ~Client() = default;

            int getSd() const {return _sd;}
            void setSd(int __sd) {_sd = __sd;}

            void init();
            void link(bool);
            void lead(rt::Scene& scene);
            void compute(rt::Scene& scene);

        private:
            struct sockaddr_in _server;

            static int _sd;
            static void _filler(rt::Scene&);
        };
    }
}

#endif /* end of include guard: NETWORK_HPP_ */

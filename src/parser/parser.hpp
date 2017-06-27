//
// parser.hpp for raytracer2 in /home/onehandedpenguin/Dev/CGP_2016/raytracer2/src/preview/load/
//
// Made by Paul Laffitte
// Login   <paul.laffitte@epitech.eu>
//
// Started on  Thu May 25 16:24:16 2017 Paul Laffitte
// Last update Sun May 28 17:37:10 2017 Paul Laffitte
//

#ifndef PARSER_HPP
# define PARSER_HPP

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include "scene.hpp"

#ifndef RED
# define RED "\033[1m\033[31m"
#endif

#ifndef BASE
# define BASE "\x1b[0m"
#endif

namespace rt
{
    class Parser
    {
    public:
        Parser(){}
        ~Parser(){}

        void loadFromFile(rt::Scene &scene, std::string const& path);
        void refresh(rt::Scene &scene);
        std::string const& getPath() const {return _path;}

    private:
        std::string *_addObject(rt::Scene &scene, std::string const& name, std::ifstream *file);
        std::string * _addObj(rt::Scene &scene, std::string const& path, std::ifstream *file);
        void _addVertices(rt::Scene &scene, AMesh const* mesh, std::vector<rt::Vector3> &vertices);
        void _loadOBJ(std::string path, std::vector<rt::Vector3> &out_vertices);
        std::string const _error(std::string const& context);

        std::string _path;
        int _lineNb = -1;
        struct timespec _lastChangeTime;
    };
}

#endif /* end of include guard: PARSER_HPP */

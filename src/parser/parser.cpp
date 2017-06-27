//
// parser.cpp for raytracer2 in /home/onehandedpenguin/Dev/CGP_2016/raytracer2/src/preview/load/
//
// Made by Paul Laffitte
// Login   <paul.laffitte@epitech.eu>
//
// Started on  Thu May 25 16:29:32 2017 Paul Laffitte
// Last update Sun May 28 18:32:03 2017 Paul Laffitte
// Last update Sun May 28 15:46:36 2017 Arthur Chaloin
//
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <exception>
#include <cstdio>
#include <cmath>
#include <math.h>
#include <string.h>
#include <sys/stat.h>
#include "texture.hpp"
#include "parser.hpp"
#include "scene.hpp"
#include "objects/sphere.hpp"
#include "objects/cylinder.hpp"
#include "objects/plane.hpp"
#include "objects/triangle.hpp"

std::string const rt::Parser::_error(std::string const& context)
{
    return std::string(_path + ":" + std::to_string(_lineNb) + ": " + RED + "parsing error: " + BASE + context);
}

#ifndef MACOS
void rt::Parser::refresh(rt::Scene &scene)
{
    struct stat statSceneFile;
    if (stat(_path.c_str(), &statSceneFile) == 0) {
        if (statSceneFile.st_mtim.tv_sec > _lastChangeTime.tv_sec) {
            _lastChangeTime = statSceneFile.st_mtim;
            scene.reset();
            loadFromFile(scene, _path);
            // Warn the user that the scene was reloaded
            system("clear");
            std::cout << "Reload scene from disk" << std::endl;
        }
    }
}
#else
void rt::Parser::refresh(rt::Scene &scene)
{
    struct stat statSceneFile;
    if (stat(_path.c_str(), &statSceneFile) == 0) {
        if (statSceneFile.st_mtimespec.tv_sec > _lastChangeTime.tv_sec) {
            _lastChangeTime = statSceneFile.st_mtimespec;
            scene.reset();
            loadFromFile(scene, _path);
            printf("%s\n", "reload!");
        }
    }
    printf(".\n");
}
#endif

std::string *rt::Parser::_addObject(rt::Scene &scene, std::string const& name, std::ifstream *file)
{
    float nb[3];
    int   inb[3];
    char line[4096];
    char token[4096];
    std::vector<rt::Vector3> vertices;

    if (name == "sphere") {
        rt::Sphere *obj = new rt::Sphere();
        obj->setRefractIndice(1);
        scene.getObjs().push_back(obj);
        _loadOBJ("../assets/sphere.obj", vertices);
    } else if (name == "cylinder") {
        rt::Cylinder *obj = new rt::Cylinder();
        scene.getObjs().push_back(obj);
        _loadOBJ("../assets/cylinder.obj", vertices);
    } else if (name == "plane") {
        rt::Plane *obj = new rt::Plane();
        scene.getObjs().push_back(obj);
        _loadOBJ("../assets/plane.obj", vertices);
    } else if (name == "camera") {
        scene.getCamera().matrix.init();
        scene.getCamera().screen_dist = -1;

        if (!file) {
            return new std::string("");
        }

        while (file->getline(line, 4096).good()) {
            _lineNb++;
            if (line[0] != ' ') {
                return new std::string(line);
            } else if (!line[0]) {
                _lineNb++;
                continue;
            }
            if (sscanf(line, " %[^:]: ", token) == 1) {
                std::string stoken(token);

                if (stoken == "position") {
                    if (sscanf(line, " %*[^:]: %f %f %f ", &nb[0], &nb[1], &nb[2]) == 3) {
                        scene.getCamera().addPosition(rt::Vector3(nb[0], nb[1], nb[2]));
                    } else {
                        throw std::runtime_error(_error("Bad arguments."));
                    }
                } else if (stoken == "rotation") {
                    if (sscanf(line, " %*[^:]: %f %f %f ", &nb[0], &nb[1], &nb[2]) == 3) {
                        scene.getCamera().addRotation(rt::Vector3(nb[0], nb[1], nb[2]));
                    } else {
                        throw std::runtime_error(_error("Bad arguments."));
                    }
                } else {
                    throw std::runtime_error(_error("Unknown instruction '" + std::string(token) + "'."));
                }
            } else {
                throw std::runtime_error(_error("Unknown instruction '" + std::string(token) + "'."));
            }
        }
    } else if (name == "light") {
        rt::Light *light = new rt::Light;
        scene.getLights().push_back(light);

        if (!file) {
            return new std::string("");
        }

        while (file->getline(line, 4096).good()) {
            _lineNb++;
            if (line[0] != ' ') {
                return new std::string(line);
            } else if (!line[0]) {
                _lineNb++;
                continue;
            }
            if (sscanf(line, " %[^:]: ", token) == 1) {
                std::string stoken(token);

                if (stoken == "position") {
                    if (sscanf(line, " %*[^:]: %f %f %f ", &nb[0], &nb[1], &nb[2]) == 3) {
                        light->setPos(rt::Vector3(nb[0], nb[1], nb[2]));
                    } else {
                        throw std::runtime_error(_error("Bad arguments."));
                    }
                } else if (stoken == "color") {
                    if (sscanf(line, " %*[^:]: %d %d %d ", &inb[0], &inb[1], &inb[2]) == 3) {
                        light->setColor(sf::Color(inb[0], inb[1], inb[2], 255));
                    } else {
                        throw std::runtime_error(_error("Bad arguments."));
                    }
                } else if (stoken == "power") {
                    if (sscanf(line, " %*[^:]: %f ", &nb[0]) == 1) {
                        light->setPower(nb[0]);
                    } else {
                        throw std::runtime_error(_error("Bad arguments."));
                    }
                } else {
                    throw std::runtime_error(_error("Unknown instruction '" + std::string(token) + "'."));
                }
            } else {
                throw std::runtime_error(_error("Unknown instruction '" + std::string(token) + "'."));
            }
        }
    } else {
        throw std::runtime_error(_error("Unknown object '" + std::string(name) + "'."));
    }

    scene.getObjs().back()->matrix.init();
    if (!file) {
        scene.getObjs().back()->addPosition(rt::Vector3(0, 0, -5));
        scene.getObjs().back()->invMatrix = scene.getObjs().back()->matrix;
        scene.getObjs().back()->invMatrix.invert();
        return new std::string("");
    }

    while (file->getline(line, 4096).good()) {
        _lineNb++;
        if (line[0] != ' ') {
            _addVertices(scene, scene.getObjs().back(), vertices);
            return new std::string(line);
        } else if (!line[0]) {
            _lineNb++;
            continue;
        }
        if (sscanf(line, " %[^:]: ", token) == 1) {
            std::string stoken(token);

            if (stoken == "position") {
                if (sscanf(line, " %*[^:]: %f %f %f ", &nb[0], &nb[1], &nb[2]) == 3) {
                    scene.getObjs().back()->addPosition(rt::Vector3(nb[0], nb[1], nb[2]));
                } else {
                    throw std::runtime_error(_error("Bad arguments."));
                }
            } else if (stoken == "rotation") {
                if (sscanf(line, " %*[^:]: %f %f %f ", &nb[0], &nb[1], &nb[2]) == 3) {
                    scene.getObjs().back()->addRotation(rt::Vector3(nb[0], nb[1], nb[2]));
                } else {
                    throw std::runtime_error(_error("Bad arguments."));
                }
            } else if (stoken == "color") {
                if (sscanf(line, " %*[^:]: %d %d %d ", &inb[0], &inb[1], &inb[2]) == 3) {
                    scene.getObjs().back()->setColor(sf::Color(inb[0], inb[1], inb[2], 255));
                } else {
                    throw std::runtime_error(_error("Bad arguments."));
                }
            } else if (stoken == "reflect") {
                if (sscanf(line, " %*[^:]: %d ", &inb[0]) == 1) {
                    scene.getObjs().back()->setReflectLevel(inb[0]);
                } else {
                    throw std::runtime_error(_error("Bad arguments."));
                }
            } else if (stoken == "param") {
                if (sscanf(line, " %*[^:]: %f ", &nb[0]) == 1) {
                    scene.getObjs().back()->setParam(nb[0]);
                } else {
                    throw std::runtime_error(_error("Bad arguments."));
                }
            } else if (stoken == "refract") {
                if (sscanf(line, " %*[^:]: %f ", &nb[0]) == 1) {
                    scene.getObjs().back()->setRefractIndice(nb[0]);
                } else {
                    throw std::runtime_error(_error("Bad arguments."));
                }
            } else if (stoken == "bump") {
                if (sscanf(line, " %*[^:]: %f ", &nb[0]) == 1) {
                    scene.getObjs().back()->setBump(nb[0]);
                } else {
                    throw std::runtime_error(_error("Bad arguments."));
                }
            } else if (stoken == "bumpScale") {
                if (sscanf(line, " %*[^:]: %f ", &nb[0]) == 1) {
                    scene.getObjs().back()->setBumpScale(nb[0]);
                } else {
                    throw std::runtime_error(_error("Bad arguments."));
                }
            } else if (stoken == "texture") {
                if (sscanf(line, " %*[^:]: %s ", token) == 1) {
                    if (!strcmp(token, "wood")) {
                        scene.getObjs().back()->setTexture(rt::TextureType::Wood);
                    } else if (!strcmp(token, "marble")) {
                        scene.getObjs().back()->setTexture(rt::TextureType::Marble);
                    } else if (!strcmp(token, "perlin")) {
                        scene.getObjs().back()->setTexture(rt::TextureType::Perlin);
                    } else {
                        scene.getObjs().back()->setTexture(rt::TextureType::None);
                    }
                } else {
                    throw std::runtime_error(_error("Bad arguments."));
                }
            } else {
                throw std::runtime_error(_error("Unknown instruction '" + std::string(token) + "'."));
            }

            scene.getObjs().back()->invMatrix = scene.getObjs().back()->matrix;
            scene.getObjs().back()->invMatrix.invert();
        } else {
            throw std::runtime_error(_error("Unknown instruction '" + std::string(token) + "'."));
        }
    }
    return nullptr;
}

void rt::Parser::loadFromFile(rt::Scene &scene, std::string const& path)
{
    std::ifstream file;
    char shebang[128];

    _lineNb = 0;
    this->_path = path;
    struct stat statSceneFile;
    if (stat(_path.c_str(), &statSceneFile) == 0) {
        #ifdef MACOS
        _lastChangeTime = statSceneFile.st_mtimespec;
        #else
        _lastChangeTime = statSceneFile.st_mtim;
        #endif
    }
    file.open(path);
    if (!(file.is_open())) {
        throw std::runtime_error(_error("Failed to open file."));
    }

    file.getline(shebang, 128);
    if (sscanf(shebang, "#! %s\n", shebang) < 1 || strcmp(BIN_PATH, shebang))  {
        throw std::runtime_error(_error("Invalid file format."));
    }

    char line[4096];
    if (!file.getline(line, 4096).good()) {
        throw std::runtime_error(_error("Invalid file format."));
    }

    char tokens[2][128];
    float nb;

    std::string *nextLine = new std::string(line);
    while (nextLine) {
        _lineNb++;
        if (!(*nextLine)[0]) {
            if (!file.getline(line, 4096).good()) {
                return;
            }
            nextLine = new std::string(line);
            _lineNb++;
            continue;
        }
        if (sscanf(line, "%[^:]: %s", tokens[0], tokens[1]) == 2
            && !strcmp(tokens[1], "default")) {
            nextLine = this->_addObject(scene, tokens[0], nullptr);
        } else if (sscanf(line, "%[^:]: %s", tokens[0], tokens[1]) == 2
            && !strcmp(tokens[0], "obj")) {
            nextLine = this->_addObj(scene, tokens[1], &file);
        } else if (sscanf(line, "%[^:]: %f", tokens[0], &nb) == 2
            && !strcmp(tokens[0], "epsilon")) {
            scene.setEpsilon(nb);
            if (!file.getline(line, 4096).good()) {
                throw std::runtime_error(_error("Invalid file format."));
            }
            nextLine = new std::string(line);
        } else if (sscanf(line, "%[^:]:", tokens[0]) == 1) {
            nextLine = this->_addObject(scene, tokens[0], &file);
        } else {
            throw std::runtime_error(_error("Unknown instruction '" + std::string(tokens[0]) + "'."));
        }
    }
}

std::string *rt::Parser::_addObj(rt::Scene &scene, std::string const& path, std::ifstream *file)
{
    float nb[3];
    int   inb[3];
    char line[4096];
    char token[4096];

    rt::Triangle *base = new rt::Triangle();
    base->matrix.init();

    while (file->getline(line, 4096).good()) {
        _lineNb++;
        if (line[0] != ' ') {
            std::vector<rt::Vector3> vertices;
            _loadOBJ(path, vertices);

            for (std::size_t i = 0; i != vertices.size(); ++i) {
                if (i % 3 == 0) {
                    rt::Triangle *triangle = new rt::Triangle(*base);
                    triangle->top[0] = vertices[i];
                    triangle->top[1] = vertices[i + 1];
                    triangle->top[2] = vertices[i + 2];
                    scene.getObjs().push_back(triangle);
                }
            }
            _addVertices(scene, static_cast<AMesh*>(base), vertices);
            return new std::string(line);
        } else if (!line[0]) {
            _lineNb++;
            continue;
        }

        if (sscanf(line, " %[^:]: ", token) == 1) {
            std::string stoken(token);

            if (stoken == "position") {
                if (sscanf(line, " %*[^:]: %f %f %f ", &nb[0], &nb[1], &nb[2]) == 3) {
                    base->addPosition(rt::Vector3(nb[0], nb[1], nb[2]));
                } else {
                    throw std::runtime_error(_error("Bad arguments."));
                }
            } else if (stoken == "rotation") {
                if (sscanf(line, " %*[^:]: %f %f %f ", &nb[0], &nb[1], &nb[2]) == 3) {
                    base->addRotation(rt::Vector3(nb[0], nb[1], nb[2]));
                } else {
                    throw std::runtime_error(_error("Bad arguments."));
                }
            } else if (stoken == "color") {
                if (sscanf(line, " %*[^:]: %d %d %d ", &inb[0], &inb[1], &inb[2]) == 3) {
                    base->setColor(sf::Color(inb[0], inb[1], inb[2], 255));
                } else {
                    throw std::runtime_error(_error("Bad arguments."));
                }
            } else if (stoken == "reflect") {
                if (sscanf(line, "%d", &inb[0]) == 1) {
                    base->setReflectLevel(inb[0]);
                } else {
                    throw std::runtime_error(_error("Bad arguments."));
                }
            } else {
                throw std::runtime_error(_error("Unknown instruction '" + std::string(token) + "'."));
            }

            base->invMatrix = base->matrix;
            base->invMatrix.invert();
        } else {
            throw std::runtime_error(_error("Unknown instruction '" + std::string(token) + "'."));
        }
    }

    std::vector<rt::Vector3> vertices;
    _loadOBJ(path, vertices);

    for (std::size_t i = 0; i != vertices.size(); ++i) {
        if (i % 3 == 0) {
            rt::Triangle *triangle = new rt::Triangle(*base);
            triangle->top[0] = vertices[i];
            triangle->top[1] = vertices[i + 1];
            triangle->top[2] = vertices[i + 2];
            scene.getObjs().push_back(triangle);
        }
    }
    _addVertices(scene, static_cast<AMesh*>(base), vertices);
    return nullptr;
}

void rt::Parser::_addVertices(rt::Scene &scene, AMesh const* mesh, std::vector<rt::Vector3> &vertices)
{
    mesh->applyParameterOnVertices(vertices);
    Vector3 light(0, -0.5, -1);
    light.normalize();
    Vector3 normal;
    for (unsigned int i = 0; i != vertices.size(); ++i) {
        if (i + 2 != vertices.size()) {
            normal = (vertices[i + 1] - vertices[i]).cross(vertices[i + 2] - vertices[i]);
            if (normal.x == 0 && normal.y == 0 && normal.z == 0) {
                normal.x = 1;
            } else {
                normal.multMatrix(mesh->matrix, 0);
                normal.normalize();
            }
        }
        scene.getVertices().push_back(vertices[i]);
        scene.getVertices().back().multMatrix(mesh->matrix, 1);
        sf::Color color = mesh->getColor();
        float lightPower = fabsf(normal * light) / 4 + 0.75;
        scene.getColors().push_back(rt::Vector3(color.r, color.g, color.b) / 255.f * lightPower);
    }
}

void rt::Parser::_loadOBJ(std::string path, std::vector<rt::Vector3> &out_vertices)
{
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<rt::Vector3> vertices;

    FILE *file = fopen(path.c_str(), "r");
    if (!file) {
        throw std::runtime_error("Failed to open file.");
    }

    while (true) {
        char type[42];
        if (fscanf(file, "%s", type) == EOF) {
            break;
        }

        if (!strcmp(type, "v")) {
            rt::Vector3 vertex;
            fscanf(file, " %f %f %f \n", &vertex.x, &vertex.y, &vertex.z);
            vertices.push_back(vertex);
        } else if (!strcmp(type, "f")) {
            unsigned int vertexIndex[3];

            int matches = fscanf(file, " %d %d %d \n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
            if (matches != 3) {
                throw std::runtime_error("Failed to load OBJ file. Wrong format?");
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
        }
    }

    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        rt::Vector3 vertex = vertices[vertexIndices[i] - 1];
        out_vertices.push_back(vertex);
    }
}

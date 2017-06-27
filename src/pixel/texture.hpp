//
// texture.hpp for rt in /home/arbona/tek1/MUL/raytracer2
//
// Made by Thomas ARBONA
// Login   <thomas.arbona@epitech.eu>
//
// Started on  Sat May 27 19:58:12 2017 Thomas ARBONA
// Last update Sun May 28 15:28:59 2017 Arthur Chaloin
//
#ifndef TEXTURE_HPP_
# define TEXTURE_HPP_

# include <SFML/Graphics.hpp>

namespace rt
{
  class AMesh;

  enum class TextureType {
    None = 0,
    Wood = 1,
    Marble = 2,
    Perlin = 3
  };

  struct TextureFunc {
    TextureType	type;
    sf::Color	(*func)(AMesh const*& obj, const float& x, const float& y, const float& z);
  };

  struct TextureColors {
    TextureType type;
    sf::Color	min;
    sf::Color	max;
  };

  class Texture
  {
  public:
    static sf::Color get(AMesh const*& obj, const float& x, const float& y, const float& z);
    static sf::Color getWood(AMesh const*& obj, const float& x, const float& y, const float& z);
    static sf::Color getMarble(AMesh const*& obj, const float& x, const float& y, const float& z);
    static sf::Color getPerlin(AMesh const*& obj, const float& x, const float& y, const float& z);

  private:
    Texture(){};
    static TextureColors getColors(TextureType type);
  };
}

#endif /* !TEXTURE_HPP_ */

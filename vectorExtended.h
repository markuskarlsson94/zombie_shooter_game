#ifndef VECTOREXTENDED_H
#define VECTOREXTENDED_H

#include <SFML/Graphics.hpp>
#include <iostream>

std::ostream& operator <<(std::ostream& os, const sf::Vector2f v);
std::ostream& operator <<(std::ostream& os, const sf::Vector2i v);
float dot(const sf::Vector2f& lv, const sf::Vector2f& rv);
float length(const sf::Vector2f & v);
sf::Vector2f normalize(sf::Vector2f v);
sf::Vector2f vectorRegulate(sf::Vector2f v, float const maxLength);
float vectorAngle(sf::Vector2f v);
sf::Vector2f vectorRotate(sf::Vector2f const & v, float const deg);
float random_range(float const min, float const max);

#endif

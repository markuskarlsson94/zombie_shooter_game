#ifndef ADDITIONAL_FUNCTIONS_H
#define ADDITIONAL_FUNCTIONS_H

#include <SFML/Graphics.hpp>

int random_range(int min, int max);
float random_range_float(float min, float max);
void setPositionCenter(sf::Vector2f pos, sf::Text & t);

#endif
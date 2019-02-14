#include "AdditionalFunctions.h"
#include <random>
#include <iostream>

int random_range(int min, int max)
{
	return (min + (std::rand() % (int)(max - min + 1)));
}
float random_range_float(float min, float max)
{
	return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}
void setPositionCenter(sf::Vector2f pos, sf::Text & t)
{
	//Must be called AFTER you've set the string
	float y = pos.y;
	float xOld = pos.x;
	float xNew = xOld - (t.getLocalBounds().width) / 2;

	t.setPosition(sf::Vector2f(xNew, y));
}
#ifndef BLOOD_H
#define BLOOD_H

#include <SFML/Graphics.hpp>
#include "BaseObject.h"
#include "SpriteObject.h"

class Blood :public BaseObject, public SpriteObject
{
public:
	Blood(EntityManager & em);
	void step(EntityManager & em, float const deltaTime, sf::RenderWindow const & window);
	void draw(sf::RenderWindow & w);
private:
	int random_range(int min, int max);
};

#endif

#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "BaseObject.h"
#include "Moveable.h"
#include "SpriteObject.h"

class EntityManager;
class Bullet : public BaseObject, public Moveable, public SpriteObject
{
public:
	Bullet(EntityManager & em, sf::Vector2f const & startPosition);
	void step(EntityManager & em, float const deltaTime, sf::RenderWindow const & window);
	void draw(sf::RenderWindow & w);
	float getRadius();
private:
	float radius{ 7.0f };
	sf::CircleShape sprite{ radius };
	float timer{ 1.0 };
};

#endif
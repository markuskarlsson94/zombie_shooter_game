#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "BaseObject.h"
#include "Moveable.h"
#include "SpriteObject.h"

class EntityManager;
class Player : public BaseObject, public Moveable, public SpriteObject
{
public:
	Player(EntityManager & em);
	void step(EntityManager & em, float const deltaTime, sf::RenderWindow const & window);
	void draw(sf::RenderWindow & w);
	sf::Vector2f mouseDirection;
	float getRadius();
	int getAmmo();
	void setAmmo(int i);
	bool isAlive();
	void setAlive(bool b);
private:
	float radius{ 15.0f };
	sf::CircleShape s{ radius };
	float shootTimer{ 0.0f };
	int ammo;
	bool alive;
};

#endif
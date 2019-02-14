#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "BaseObject.h"
#include "Moveable.h"
#include "SpriteObject.h"

class EntityManager;
class Enemy : public BaseObject, public Moveable, public SpriteObject
{
public:
	Enemy(EntityManager & em);
	void step(EntityManager & em, float const deltaTime, sf::RenderWindow const & window);
	void draw(sf::RenderWindow & w);
	void setHitRadius(float f);
	float getHitRadius();
	void setMoveTimer();
	void setMoveTimerMax(float f);
	void setHp(int i);
	void damage(int damage);
	sf::Vector2f playerDir;
private:
	float radius{ 10.0f };
	sf::CircleShape hitCircle;
	bool drawHitRadius = false;
	float moveTimer = 0.0f;
	float moveTimerMax = 1.5f;
	bool moving = 1;
	int hp = 5;
};

#endif
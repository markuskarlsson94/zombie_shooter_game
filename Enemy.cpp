#include "Enemy.h"
#include "EntityManager.h"
#include "Player.h"
#include "vectorExtended.h"
#include "GameControl.h"
#include <iostream>

Enemy::Enemy(EntityManager & em)
{
	name = "Enemy";
	setHitRadius(25.0f);
	drawHitRadius = false;
	
	//Set up moveable
	Moveable::setSpeed(sf::Vector2f{ 0.0f,0.0f });
	Moveable::setAcceleration(1600.0f);
	Moveable::setFriction(1200.0f);
	Moveable::setBounceAgainstBorders(false);
	Moveable::setMaxSpeed(250.0f);
	Moveable::setMaxMoveSpeed(100.0f);
	Moveable::setShapeRadius(getHitRadius());

	//Set up spriteobject
	SpriteObject::setSprite(em, "Zombie");
	SpriteObject::setOrigin(100.0f, 155.0f);
	float scale = 0.3f;
	SpriteObject::setScale(scale, scale);
	SpriteObject::setAnimation(sf::Vector2i(288, 311), 17, 0, 30.0f);
}
void Enemy::step(EntityManager & em, float const deltaTime, sf::RenderWindow const & window)
{
	//Destroy if health is 0
	if (hp <= 0)
	{
		em.getGameControl()->increaseScore(1);
		destroy();
	}

	//Get the player addres
	Player* p = em.getPlayer();

	if (p != nullptr && em.getPlayer()->isAlive())
	{
		//Get the direction towrds the player and rotate the sprite accordingly
		playerDir = p->Moveable::getPosition() - Moveable::getPosition();
		SpriteObject::setRotation(vectorAngle(playerDir));

		//Decrease movetimer
		if (moveTimer > 0.0f)
		{
			moveTimer -= deltaTime;
		}

		//Move towards player if timer is 0
		if (moveTimer <= 0.0)
		{
			Moveable::move(playerDir, deltaTime);
			SpriteObject::update(deltaTime);
		}
	}
	
	//Update position
	Moveable::update(em, deltaTime);
	SpriteObject::setPosition(Moveable::getPosition());
	hitCircle.setPosition(getPosition() - sf::Vector2f{ radius,radius });

	//Check collision with player
	if (p->isAlive())
	{
		//Kill the player
		if (length(getPosition() - (p->getPosition())) < radius + p->getRadius())
		{
			p->setAlive(false);
		}
	}


}
void Enemy::draw(sf::RenderWindow & w)
{
	if (drawHitRadius == true)
	{
		w.draw(hitCircle);
	}
	SpriteObject::draw(w);
}
void Enemy::setHitRadius(float f)
{
	radius = f;
	hitCircle.setRadius(radius);
}
float Enemy::getHitRadius()
{
	return radius;
}
void Enemy::setMoveTimer()
{
	moveTimer = moveTimerMax;
}
void Enemy::setMoveTimerMax(float f)
{
	moveTimerMax = f;
}
void Enemy::setHp(int i)
{
	hp = i;
}
void Enemy::damage(int damage)
{
	hp -= damage;
}
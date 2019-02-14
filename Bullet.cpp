#include "Bullet.h"
#include "EntityManager.h"
#include "Enemy.h"
#include "Blood.h"
#include "vectorExtended.h"

Bullet::Bullet(EntityManager & em, sf::Vector2f const & startPosition)
{
	Moveable::setPosition(startPosition);

	//SpriteObject::loadSprite("Bullet.png");
	SpriteObject::setSprite(em, "Bullet");
	SpriteObject::setOrigin(0.0f, 120.0f);
	float scale = 0.04f;
	SpriteObject::setScale(scale, scale);
	SpriteObject::setPosition(Moveable::getPosition());
	
	//sprite.setPosition(Moveable::getPosition());
	name = "Bullet";
}
void Bullet::step(EntityManager & em, float const deltaTime, sf::RenderWindow const & window)
{
	Moveable::update(em, deltaTime);

	//Collisions
	for (int i = 0; i < em.enemyCount(); ++i)
	{
		Enemy* enemy = em.getEnemy(i);
		if (length(getPosition() - (enemy->getPosition())) < radius + enemy->getHitRadius())
		{
			remove = true;
			enemy->damage(1);
			enemy->Moveable::addSpeed(getSpeed() / 4.0f);
			enemy->setMoveTimer();

			sf::Vector2f direction = normalize(Moveable::getSpeed());
			Blood* blood = new Blood(em);
			blood->setPosition(Moveable::getPosition()+direction*30.0f);
			blood->setRotation(vectorAngle(Moveable::getSpeed()));
			em.addBlood(blood);
			break;
		}
	}

	/*for (int i = 0; i < em.objectCount(); ++i)
	{
		//??????????????????????????????
		BaseObject* b = em.at(i);
		BaseObject* temp = em.at(i);
		Moveable* other;
		other = dynamic_cast<Moveable*>(b);

		//BaseObject* other = em.at(i);
		//Error: baseObject has no member getPosition()

		if (other != this) //Dont compare against yourself
		{
			if (temp->getName() == "Enemy") //Code for enemy collision
			{
				if (length(getPosition() - (other->getPosition())) < radius + other->getRadius())
				{
					remove = true;
					//other->destroy();
					other->addSpeed(getSpeed() / 3.0f);
					break;
				}
			}
		}
	}*/

	//sprite.setPosition(Moveable::getPosition() - sf::Vector2f{ radius,radius });
	SpriteObject::setPosition(Moveable::getPosition());
	timer -= deltaTime;
	if (timer <= 0)
	{
		remove = true;
	}
}
void Bullet::draw(sf::RenderWindow & w)
{
	//w.draw(sprite);
	SpriteObject::draw(w);
}
float Bullet::getRadius()
{
	return radius;
}
#include "Player.h"
#include "Bullet.h"
#include "EntityManager.h"
#include "vectorExtended.h"
#include "SpriteObject.h"
#include "Ammo.h"
#include <iostream>

Player::Player(EntityManager & em)
{
	//setup moveable
	Moveable::setPosition(sf::Vector2f{ 400.0f, 300.0f });
	Moveable::setSpeed(sf::Vector2f{ 0.0f,0.0f });
	Moveable::setAcceleration(3600.0f);
	Moveable::setFriction(1200.0f);
	Moveable::setBounceAgainstBorders(true);
	Moveable::setMaxSpeed(250.0f);
	Moveable::setMaxMoveSpeed(250.0f);
	Moveable::setShapeRadius(getRadius());

	//setup spriteobject
	SpriteObject::setSprite(em, "Player");
	SpriteObject::setOrigin(60.0f, 117.0f);
	float scale = 0.3f;
	SpriteObject::setScale(scale, scale);

	SpriteObject::setPosition(getPosition() - sf::Vector2f{ radius,radius });
	setAmmo(50);
	setAlive(true);
	name = "Player";
}
void Player::step(EntityManager & em, float const deltaTime, sf::RenderWindow const & window)
{
	//Movement------------------------------------------------------------------------------
	if (alive == true)
	{
		//Get the direction you want to move in
		sf::Vector2f dir = { 0.0f,0.0f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			dir.y--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			dir.x--;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			dir.y++;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			dir.x++;
		}

		//Move in that direction
		Moveable::move(dir, deltaTime);
	}
	Moveable::update(em, deltaTime);

	//Shooting-----------------------------------------------------------------------------
	//Get the direction of the mouse relative to the player
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
	mouseDirection = normalize(mousePos - getPosition());

	//Decrease timer
	if (shootTimer>0)
	{
		shootTimer -= deltaTime;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && shootTimer <= 0 && ammo>0 && alive==true)
	{
		//Only shoot if mouse is within window
		if (mousePos.x >= 0 && mousePos.x <= em.getWidth() && mousePos.y >= 0 && mousePos.y <= em.getHeight())
		{
			//Slightly offset the direction to shoot in
			float offset = 4.0;
			sf::Vector2f temp = vectorRotate(mouseDirection, random_range(-offset, offset));

			//Spawn bullet
			Bullet* bullet = new Bullet(em, getPosition() + mouseDirection* 35.0f);
			bullet->setSpeed(temp*1500.0f);
			bullet->setRotation(vectorAngle(temp));
			em.addBullet(bullet);
			--ammo;

			//Set a timer until you can shoot again
			shootTimer = 0.1f;
			Moveable::addSpeed(-mouseDirection*70.0f);
		}
	}

	//Collision with ammo object
	if (em.getAmmo()!=nullptr)
	{
		if (em.getAmmo()->getActive() == true)
		{
			Ammo* ammo = em.getAmmo();
			if (length(getPosition() - (ammo->getPosition())) < radius + ammo->getShapeRadius())
			{
				setAmmo(50);
				em.getAmmo()->setActive(false);
			}
		}
	}

	//Move sprite
	//s.setPosition(getPosition() - sf::Vector2f{ radius,radius });
	SpriteObject::setPosition(Moveable::getPosition());
	if (alive == true)
	{
		SpriteObject::setRotation(vectorAngle(mouseDirection));
	}
}
void Player::draw(sf::RenderWindow & w)
{
	//w.draw(s);
	//std::cout << "player dreaw" << std::endl;
	SpriteObject::draw(w);
}
float Player::getRadius()
{
	return radius;
}
int Player::getAmmo()
{
	return ammo;
}
void Player::setAmmo(int i)
{
	ammo=i;
}
bool Player::isAlive()
{
	return alive;
}
void Player::setAlive(bool b)
{
	alive = b;
}

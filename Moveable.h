#ifndef MOVEABLE_H
#define MOVEABLE_H

#include <SFML/Graphics.hpp>
//#include "EntityManager.h"
class EntityManager;
class Moveable
{
public:
	//Setters
	void setPosition(sf::Vector2f const & v);
	void setX(float const f);
	void setY(float const f);
	void setSpeed(sf::Vector2f const & v);
	void setAcceleration(float const f);
	void setFriction(float const f);
	void setMaxSpeed(float const f);
	void setMaxMoveSpeed(float const f);
	void setBounceAgainstBorders(bool b);
	void setShapeRadius(float const f);

	//Getters
	sf::Vector2f getPosition();
	float getX();
	float getY();
	sf::Vector2f getSpeed();
	float getAcceleration();
	float getFriction();
	float getMaxSpeed();
	bool getBounceAgainstBorders();
	float getShapeRadius();

	//Modifiers
	void addSpeed(sf::Vector2f const & v);
	void addMoveSpeed(sf::Vector2f const & v);
	void update(EntityManager & em, float const deltaTime);
	void move(sf::Vector2f const & direction, float const deltaTime);

	//Destructor
	//~virtual Moveable() {}

private:
	sf::Vector2f position = { 0.0f,0.0f };
	sf::Vector2f speed = { 0.0f,0.0f };
	sf::Vector2f moveSpeed = { 0.0f,0.0f };
	//sf::Vector2f addMoveSpeed = { 0.0f,0.0f };
	float acceleration = 0.0f;
	float friction = 0.0f;
	float maxSpeed = 100.0f;
	float maxMoveSpeed = 50.0f;
	bool bounceAgainstBorders = false;
	float shapeRadius = 1.0f;
};

#endif

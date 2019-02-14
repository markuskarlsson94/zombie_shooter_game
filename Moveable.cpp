#include "Moveable.h"
#include "vectorExtended.h"
#include "EntityManager.h"

//Setters
void Moveable::setPosition(sf::Vector2f const & v)
{
	position = v;
}
void Moveable::setX(float const f)
{
	position.x = f;
}
void Moveable::setY(float const f)
{
	position.y = f;
}
void Moveable::setSpeed(sf::Vector2f const & v)
{
	speed = v;
}
void Moveable::setAcceleration(float const f)
{
	acceleration = f;
}
void Moveable::setFriction(float const f)
{
	friction = f;
}
void Moveable::setMaxSpeed(float const f)
{
	maxSpeed = f;
}
void Moveable::setMaxMoveSpeed(float const f)
{
	maxMoveSpeed = f;
}
void Moveable::setBounceAgainstBorders(bool b)
{
	bounceAgainstBorders = b;
}
void Moveable::setShapeRadius(float const f)
{
	shapeRadius = f;
}

//Getters
sf::Vector2f Moveable::getPosition()
{
	return position;
}
float Moveable::getX()
{
	return position.x;
}
float Moveable::getY()
{
	return position.y;
}
sf::Vector2f Moveable::getSpeed()
{
	return speed;
}
float Moveable::getAcceleration()
{
	return acceleration;
}
float Moveable::getFriction()
{
	return friction;
}
float Moveable::getMaxSpeed()
{
	return maxSpeed;
}
bool Moveable::getBounceAgainstBorders()
{
	return bounceAgainstBorders;
}
float Moveable::getShapeRadius()
{
	return shapeRadius;
}

//Modifiers
void Moveable::addSpeed(sf::Vector2f const & v)
{
	speed += v;
	speed = vectorRegulate(speed, maxSpeed); //Regulate speed //250
}
void Moveable::addMoveSpeed(sf::Vector2f const & v)
{
	moveSpeed += v;
	moveSpeed = vectorRegulate(moveSpeed, maxMoveSpeed);
}
void Moveable::move(sf::Vector2f const & direction, float const deltaTime)
{
	//Moves the object in the direction given by the input vector using acceleration
	sf::Vector2f dir = normalize(direction);
	addMoveSpeed((acceleration*deltaTime)*dir);
}
void Moveable::update(EntityManager & em, float const deltaTime)
{
	//Update position
	position += (speed + moveSpeed)*deltaTime;

	//Friction
	if (friction > 0.0f)
	{
		//Speed
		sf::Vector2f f = normalize(speed)*friction*deltaTime;
		if (length(speed) >= length(f))
		{
			speed -= f;
		}
		else
		{
			//Prevent jittering
			speed = { 0.0f,0.0f };
		}

		//MoveSpeed
		f = normalize(moveSpeed)*friction*deltaTime;
		if (length(moveSpeed) >= length(f))
		{
			moveSpeed -= f;
		}
		else
		{
			//Prevent jittering
			moveSpeed = { 0.0f,0.0f };
		}
	}

	if (bounceAgainstBorders == true)
	{
		int width = em.getWidth();
		int height = em.getHeight();

		//Bounce against window borders
		if (position.x < 0.0f + shapeRadius)
		{
			//Left border
			position.x = 0.0 + shapeRadius;
			//speed.x *= -1.0f;
			//speed *= 0.5f;
		}
		if (position.x > width - shapeRadius)
		{
			//Right border
			position.x = width - shapeRadius;
			//speed.x *= -1.0f;
			//speed *= 0.5f;
		}
		if (position.y < 0.0f + shapeRadius)
		{
			//Upper border
			position.y = 0.0 + shapeRadius;
			//speed.y *= -1.0f;
			//speed *= 0.5f;
		}
		if (position.y > height - shapeRadius)
		{
			//Lower border
			position.y = height - shapeRadius;
			//speed.y *= -1.0f;
			//speed *= 0.5f;
		}
	}
}

//Destructor
//~virtual Moveable() {}
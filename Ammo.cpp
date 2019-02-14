#include "Ammo.h"

Ammo::Ammo(EntityManager &em)
{
	Moveable::setPosition(sf::Vector2f(320.0, 250.0f));
	Moveable::setShapeRadius(20.0f);

	SpriteObject::setSprite(em, "Ammo");
	SpriteObject::setOrigin(20.0f, 20.0f);
	SpriteObject::setPosition(Moveable::getPosition());

	name = "Ammo";
}
void Ammo::draw(sf::RenderWindow & w)
{
	if (active == true)
	{
		SpriteObject::draw(w);
	}
}
void Ammo::setActive(bool b)
{
	active = b;
}
bool Ammo::getActive()
{
	return active;
}
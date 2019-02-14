#ifndef AMMO_H
#define AMMO_H

#include <SFML/Graphics.hpp>
#include "BaseObject.h"
#include "SpriteObject.h"
#include "Moveable.h"

class EntityManager;
class Ammo : public BaseObject, public SpriteObject, public Moveable
{
public:
	Ammo(EntityManager &em);
	void draw(sf::RenderWindow & w);
	void setActive(bool b);
	bool getActive();
private:
	bool active = true;
};

#endif

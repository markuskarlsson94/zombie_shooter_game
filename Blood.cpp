#include "Blood.h"
#include "EntityManager.h"
#include "AdditionalFunctions.h"

Blood::Blood(EntityManager & em)
{



	int b = random_range(1, 6);


	if (b == 1) { SpriteObject::setSprite(em, "Blood1"); }
	else if (b == 2) { SpriteObject::setSprite(em, "Blood2"); }
	else if (b == 3) { SpriteObject::setSprite(em, "Blood3"); }
	else if (b == 4) { SpriteObject::setSprite(em, "Blood4"); }
	else if (b == 5) { SpriteObject::setSprite(em, "Blood5"); }
	else if (b == 6) { SpriteObject::setSprite(em, "Blood6"); }

	SpriteObject::setScale(random_range_float(0.1f, 1.0f), random_range_float(0.1f, 3.0f));
	SpriteObject::setOrigin(0.0f, 30.0f);
}
void Blood::step(EntityManager & em, float const deltaTime, sf::RenderWindow const & window)
{
	//do nothing
}
void Blood::draw(sf::RenderWindow & w)
{
	SpriteObject::draw(w);
}
int Blood::random_range(int min, int max)
{
	return (min + (rand() % (int)(max - min + 1)));
}

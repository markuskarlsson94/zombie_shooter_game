#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include <SFML/Graphics.hpp>

class EntityManager;
class SpriteObject
{
public:
	//Setters
	void setSprite(EntityManager & em, std::string name);
	void setPosition(sf::Vector2f const & v);
	void setRotation(float angle);
	void setOrigin(float x, float y);
	void setScale(float x, float y);
	void setAnimation(sf::Vector2i frameSize, int frames, int startingFrame, float framesPerSecond);

	//Getters
	sf::Sprite getSprite();

	//Other
	void update(float const deltaTime);
	void draw(sf::RenderWindow & w);

private:
	sf::Sprite sprite;
	sf::Texture texture;

	//Animation specific members
	sf::Vector2i aniFrameSize;
	int aniFrame=0;
	int aniFrames = 1;
	float aniFramesPerSecond;
	float framesTimer = 0.0f;
};

#endif
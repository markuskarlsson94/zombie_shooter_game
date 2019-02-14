#include "SpriteObject.h"
#include "EntityManager.h"
#include <iostream>

//Constructor

//Setters
void SpriteObject::setSprite(EntityManager & em, std::string name)
{
	sprite.setTexture(em.getTexture(name));
}
void SpriteObject::setPosition(sf::Vector2f const & v)
{
	sprite.setPosition(v);
}
void SpriteObject::setRotation(float angle)
{
	sprite.setRotation(angle);
}
void SpriteObject::setOrigin(float x, float y)
{
	sprite.setOrigin(x, y);
}
void SpriteObject::setScale(float x, float y)
{
	sprite.setScale(x, y);
}
void SpriteObject::setAnimation(sf::Vector2i frameSize, int frames, int startingFrame, float framesPerSecond)
{
	aniFrameSize = frameSize;
	aniFrames = frames;
	aniFrame = startingFrame;
	aniFramesPerSecond = framesPerSecond;
	sprite.setTextureRect(sf::IntRect(aniFrameSize.x*aniFrame,0,aniFrameSize.x,aniFrameSize.y));
}

//Getters
sf::Sprite SpriteObject::getSprite()
{
	return sprite;
}

//Other

void SpriteObject::update(float const deltaTime)
{
	if (aniFrames > 1)
	{
		framesTimer += deltaTime;
		if (framesTimer >= (1 / aniFramesPerSecond))
		{
			framesTimer = 0.0f;
			if (aniFrame < aniFrames-1)
			{
				aniFrame++;
			}
			else
			{
				aniFrame = 0;
			}
			sprite.setTextureRect(sf::IntRect(aniFrameSize.x*aniFrame, 0, aniFrameSize.x, aniFrameSize.y));
		}
	}
}
void SpriteObject::draw(sf::RenderWindow & w)
{
	w.draw(sprite);
}
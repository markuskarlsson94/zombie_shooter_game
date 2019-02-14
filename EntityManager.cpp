#include "EntityManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GameControl.h"
#include "Ammo.h"
#include "Blood.h"
#include <iostream>

//Player class functions
void EntityManager::setPlayer(Player* p)
{
	player = p;
}
Player* EntityManager::getPlayer()
{
	return player;
}
void EntityManager::removePlayer()
{
	player = nullptr;
}

//Enemy class functions
void EntityManager::addEnemy(Enemy* & e)
{
	vectorEnemy.push_back(e);
}
Enemy* EntityManager::getEnemy(int const i)
{
	return vectorEnemy.at(i);
}
int EntityManager::enemyCount()
{
	return vectorEnemy.size();
}
void EntityManager::clearEnemies()
{
	for(auto &i : vectorEnemy)
	{
		i->destroy();
	}
}

//Bullet class functions
void EntityManager::addBullet(Bullet* & b)
{
	vectorBullet.push_back(b);
}
Bullet* EntityManager::getBullet(int const i)
{
	return vectorBullet.at(i);
}
int EntityManager::bulletCount()
{
	return vectorBullet.size();
}
void EntityManager::clearBullets()
{
	for (auto &i : vectorBullet)
	{
		i->destroy();
	}
}

//Ammo class functions
void EntityManager::setAmmo(Ammo* a)
{
	ammo = a;
}
Ammo* EntityManager::getAmmo()
{
	return ammo;
}
void EntityManager::removeAmmo()
{
	ammo = nullptr;
}

//Blood class functions
void EntityManager::addBlood(Blood* b)
{
	vectorBlood.push_back(b);
}
Blood* EntityManager::getBlood(int const i)
{
	return vectorBlood.at(i);
}
int EntityManager::bloodCount()
{
	return vectorBullet.size();
}
void EntityManager::clearBlood()
{
	for (auto &i : vectorBlood)
	{
		i->destroy();
	}
}

//GameControl class functions
void EntityManager::setGameControl(GameControl* g)
{
	gamecontrol = g;
}
GameControl* EntityManager::getGameControl()
{
	return gamecontrol;
}
void EntityManager::removeGameControl()
{
	gamecontrol = nullptr;
}

//Texture map functions
void EntityManager::addTexture(std::string name, sf::Texture texture)
{
	//insert texture
	std::pair<std::map<std::string, sf::Texture>::iterator, bool> ret;
	ret = textureMap.insert(std::pair<std::string, sf::Texture>(name, texture));
	if (ret.second == false) 
	{
		std::cout << "Error: texture already exists";
	}
}
sf::Texture& EntityManager::getTexture(std::string name)
{
	return textureMap.at(name);
}

//Font functions
void EntityManager::setFont(sf::Font const & f)
{
	font = f;
}
sf::Font& EntityManager::getFont()
{
	//std::cout << "hej" << std::endl;
	return font;
}

void EntityManager::update(EntityManager & em, float const deltaTime, sf::RenderWindow const & window)
{
	//Gamecontrol
	if (gamecontrol != nullptr)
	{
		gamecontrol->update(em, deltaTime);
	}

	//Blood
	for (int i = 0; i<vectorBlood.size(); ++i)
	{
		if (vectorBlood.at(i)->shouldRemove())
		{
			vectorBlood.erase(vectorBlood.begin() + i);
		}
		else
		{
			//vectorBullet.at(i)->step(em, deltaTime, window);
		}
	}

	//Player
	if (player != nullptr)
	{
		if (player->shouldRemove())
		{
			removePlayer();
		}
		else
		{
			player->step(em, deltaTime, window);
		}
	}
	
	//Enemies
	for (int i = 0; i<vectorEnemy.size(); ++i)
	{
		if (vectorEnemy.at(i)->shouldRemove())
		{
			vectorEnemy.erase(vectorEnemy.begin() + i);
		}
		else
		{
			vectorEnemy.at(i)->step(em, deltaTime, window);
		}
	}

	//Bullets
	for (int i = 0; i<vectorBullet.size(); ++i)
	{
		if (vectorBullet.at(i)->shouldRemove() == true)
		{
			vectorBullet.erase(vectorBullet.begin() + i);
		}
		else
		{
			vectorBullet.at(i)->step(em, deltaTime, window);
		}
	}
}
void EntityManager::draw(sf::RenderWindow & w) const
{
	for (int i = 0; i<vectorBlood.size(); ++i)
	{
		vectorBlood.at(i)->draw(w);
	}
	if (player != nullptr)
	{
		//std::cout << "dff" << std::endl;
		player->draw(w);
	}
	for (int i = 0; i<vectorEnemy.size(); ++i)
	{
		vectorEnemy.at(i)->draw(w);
	}
	for (int i = 0; i<vectorBullet.size(); ++i)
	{
		vectorBullet.at(i)->draw(w);
	}
	if (ammo != nullptr)
	{
		ammo->draw(w);
	}
	if (gamecontrol != nullptr)
	{
		gamecontrol->draw(w);
	}
}
int EntityManager::entityCount()
{
	int count = 0;
	count += vectorEnemy.size() + vectorBullet.size() +vectorBlood.size();
	if (getPlayer() != nullptr)
	{
		count++;
	}
	if (getGameControl() != nullptr)
	{
		count++;
	}

	return count;
}
int EntityManager::getWidth()
{
	return WIDTH;
}
int EntityManager::getHeight()
{
	return HEIGHT;
}
EntityManager::~EntityManager()
{
	//Remove each object

	for (auto &i : vectorEnemy)
	{
		delete i;
	}

	for (auto &i : vectorBullet)
	{
		delete i;
	}

	for (auto&i : vectorBlood)
	{
		delete i;
	}
}

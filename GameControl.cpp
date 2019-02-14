#include "GameControl.h"
#include "Enemy.h"
#include "EntityManager.h"
#include "Player.h"
#include "Ammo.h"
#include "AdditionalFunctions.h"
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include "vectorExtended.h"
#include <SFML/Graphics.hpp>

GameControl::GameControl(EntityManager & em)
{
	Player* p = em.getPlayer();
	spawnTimer = 2.0f;
	spawnTimerMax = 2.0f;


	//Score text
	scoreText.setFont(em.getFont());
	scoreText.setCharacterSize(20);
	std::stringstream ss;
	ss << "Score: " << std::to_string(score);
	scoreText.setString(ss.str());
	setPositionCenter(sf::Vector2f{ 400.0f, 15.0f }, scoreText);
	
	//Ammo text
	ammoText.setFont(em.getFont());
	ammoText.setCharacterSize(20);
	ammoText.setPosition(sf::Vector2f(15.0f, 15.0f));
	ss.str(std::string());
	ss.clear();
	ss << "Ammo: " << std::to_string(p->getAmmo());
	ammoText.setString(ss.str());

	//Game over text
	gameOverText.setFont(em.getFont());
	gameOverText.setCharacterSize(20);
	gameOverText.setString("You have died. Press \"space\" to restart");
	setPositionCenter(sf::Vector2f{ 400.0f, 200.0f }, gameOverText);

	//Instruction text
	instructionText.setFont(em.getFont());
	instructionText.setCharacterSize(20);
	instructionText.setString("Controls: Move with WASD and shoot with the mouse.");
	setPositionCenter(sf::Vector2f{ 400.0f, 200.0f }, instructionText);

	//Set up rectangle
	rect.setFillColor(sf::Color(0, 0, 0, 130));
	rect.setSize(sf::Vector2f{ 800.0f, 600.0f });

	state = "start";
	stateTimer = 5.0f;
}
void GameControl::update(EntityManager & em, float const deltaTime)
{
	Player* p = em.getPlayer();

	//Update ammo text
	std::stringstream ss;
	ss << "Ammo: " << std::to_string(p->getAmmo());
	ammoText.setString(ss.str());

	//Activate the ammo object if the player has run out of bullets and it is inactive
	Ammo* a = em.getAmmo();
	if (em.getPlayer()->getAmmo() <= 0 && a->getActive() == false)
	{
		a->setActive(true);
		sf::Vector2f spawnPosition;
		spawnPosition.x = random_range(50, em.getWidth()-50);
		spawnPosition.y = random_range(50, em.getHeight()-50);
		a->Moveable::setPosition(spawnPosition);
		a->SpriteObject::setPosition(spawnPosition);
	}

	//Game state control
	if (state == "start")
	{
		if (stateTimer > 0.0f)
		{
			stateTimer -= deltaTime;
			if (stateTimer <= 0.0f)
			{
				//gameStart(em);
				state = "running";
			}
		}
	}
	if (state == "running")
	{
		if (!p->isAlive())
		{
			//If the player is dead, set a timer
			stateTimer = 2.0f;
			state = "end";
			setPositionCenter(sf::Vector2f{ 400.0f,170.0f }, scoreText);
		}
	     
		spawnTimer-=deltaTime;

		if (spawnTimer<=0.0)
		{
		    spawnEnemy(em);

		    if (spawnTimerMax>0.5f)
		    {
			spawnTimerMax-=0.01;
		    }
		    spawnTimer=spawnTimerMax;
		}

	}
	else if (state == "end")
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			gameRestart(em);
			setPositionCenter(sf::Vector2f{ 400.0f,15.0f }, scoreText);
			state = "start";
			stateTimer = 5.0f;
		}
	}
}
void GameControl::draw(sf::RenderWindow & w)
{
	if (state == "start")
	{
		w.draw(instructionText);
		w.draw(ammoText);
	}
	else if (state == "running")
	{
		w.draw(ammoText);
	}
	if (state == "end")
	{
		w.draw(rect);
		w.draw(gameOverText);
	}
	w.draw(scoreText);
}

void GameControl::spawnEnemy(EntityManager & em)
{
	Enemy* enemy = new Enemy(em);

	//Choose which side to spawn on
	int side = random_range(1, 4);
	float offset = 30.0f;

	//Left
	if (side == 1)
	{
		enemy->Moveable::setPosition(sf::Vector2f(-offset, random_range(0, em.getHeight())));
	}
	//Right
	else if (side == 2)
	{
		enemy->Moveable::setPosition(sf::Vector2f(em.getWidth()+ offset, random_range(0, em.getHeight())));
	}
	//Up
	else if (side == 3)
	{
		enemy->Moveable::setPosition(sf::Vector2f(random_range(0,em.getWidth()), -offset));
	}
	//Down
	else if (side == 4)
	{
		enemy->Moveable::setPosition(sf::Vector2f(random_range(0, em.getWidth()), em.getHeight()+ offset));
	}

	int spawnChance = random_range(1, 10);

	if (spawnChance == 1 || spawnChance == 2)
	{
		//Init a big enemy
		enemy->setScale(0.45f, 0.45f);
		enemy->setMaxMoveSpeed(random_range_float(150.0f,160.0f));
		enemy->setHp(10); 
		enemy->setMoveTimerMax(0.0f);
	}
	else if (spawnChance == 3)
	{
	        //Init a small enemy
		enemy->setScale(0.25f, 0.25f);
		enemy->setMaxMoveSpeed(random_range_float(250.0f,260.0f));
		enemy->setHp(2);
		enemy->setMoveTimerMax(1.0f);
	}
	else
	{
		//Init regular enemy
		enemy->setMaxMoveSpeed(random_range_float(80.0f, 120.0f));
	}
	
	//Spawn enemy
		em.addEnemy(enemy);
}
void GameControl::increaseScore(int i)
{
	score += i;
	std::stringstream ss;
	ss << "Score: " << std::to_string(score);
	scoreText.setString(ss.str());
	setPositionCenter(sf::Vector2f{ 400.0f, 15.0f }, scoreText);
}
void GameControl::setScore(int i)
{
	score = 0;
	std::stringstream ss;
	ss << "Score: " << std::to_string(score);
	scoreText.setString(ss.str());
}
void GameControl::gameRestart(EntityManager & em)
{
	//Clear enemies and bullets
	em.clearEnemies();
	em.clearBullets();

	//Clear blood
	em.clearBlood();

	//Reset player
	Player* p = em.getPlayer();
	p->Moveable::setPosition(sf::Vector2f{ 400.0f,300.0f });
	p->setAmmo(50);
	p->setSpeed(sf::Vector2f{ 0.0f,0.0f });
	p->setAlive(true);

	//Reset score
	setScore(0);
	spawnTimer = 2.0f;
	spawnTimerMax=2.0f;


	//Reset ammo pickup
	em.getAmmo()->setActive(false);
}
void GameControl::setState(std::string s)
{
	state = s;
}
std::string GameControl::getState()
{
	return state;
}
float GameControl::getStateTimer()
{
	return stateTimer;
}
float GameControl::getSpawnTimer()
{
    return spawnTimer;
}

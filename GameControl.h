#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <SFML/Graphics.hpp>

class EntityManager;
class GameControl
{
public:
	GameControl(EntityManager & em);
	void update(EntityManager & em, float const deltaTime);
	void draw(sf::RenderWindow & w);
	void spawnEnemy(EntityManager & em);
	void increaseScore(int i);
	void setScore(int i);
	void gameRestart(EntityManager & em);
	void setState(std::string s);
	std::string getState();
	float getStateTimer();
	float getSpawnTimer();
private:
	int score=0;
	float spawnTimer;
	float spawnTimerMax;
	sf::Text scoreText;
	sf::Text ammoText;
	sf::Text gameOverText;
	sf::Text instructionText;
	sf::RectangleShape rect;
	std::string state;
	float stateTimer = 0.0f;
	
};

#endif

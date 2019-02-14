#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

class BaseObject;
class Player;
class Enemy;
class Bullet;
class GameControl;
class Ammo;
class Blood;

class EntityManager
{
public:
	//Player class functions
	void setPlayer(Player* p);
	Player* getPlayer();
	void removePlayer();

	//Enemy class functions
	void addEnemy(Enemy* & e);
	Enemy* getEnemy(int const i);
	int enemyCount();
	void clearEnemies();

	//Bullet class functions
	void addBullet(Bullet* & b);
	Bullet* getBullet(int const i);
	int bulletCount();
	void clearBullets();

	//Ammo class functions
	void setAmmo(Ammo* a);
	Ammo* getAmmo();
	void removeAmmo();

	//Blood class functions
	void addBlood(Blood* b);
	Blood* getBlood(int const i);
	int bloodCount();
	void clearBlood();

	//GameControl class functions
	void setGameControl(GameControl* g);
	GameControl* getGameControl();
	void removeGameControl();

	//Texture map functions
	void addTexture(std::string name, sf::Texture texture);
	sf::Texture& getTexture(std::string name);

	//Font functions
	void setFont(sf::Font const & f);
	sf::Font& getFont();

	void update(EntityManager & em, float const deltaTime, sf::RenderWindow const & window);
	void draw(sf::RenderWindow & w) const;
	int entityCount();
	int getWidth();
	int getHeight();
	~EntityManager();
private:
	//multimap<pair<int drawOrder, BaseObject*>> v; //sort by drawOrder
	std::vector<Enemy*> vectorEnemy;
	std::vector<Bullet*> vectorBullet;
	std::vector<Blood*> vectorBlood;

	GameControl* gamecontrol = nullptr;
	Player* player = nullptr;
	Ammo* ammo = nullptr;

	std::map<std::string, sf::Texture> textureMap;
	sf::Font font;

	const int WIDTH = 800;
	const int HEIGHT = 600;
};

#endif
#include <SFML/Graphics.hpp>

//VS specific. Cant use M_PI otherwise
//#define _USE_MATH_DEFINES
//#include <cmath>
//-----------------
#include <iostream>
#include <sstream>
//#include <math.h>
#include <iomanip>
#include <iterator>
#include <random>

#include "vectorExtended.h"
#include "BaseObject.h"
#include "EntityManager.h"
#include "Moveable.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "SpriteObject.h"
#include "GameControl.h"
#include "Ammo.h"
#include "AdditionalFunctions.h"

using namespace std;
using sf::Vector2f;
using sf::Vector2i;

const int WIDTH = 800;
const int HEIGHT = 600;

void loadTexture(EntityManager &em, sf::Texture &t, string const &source, string const &name)
{
	if (!t.loadFromFile(source))
	{
		cout << "Error: Failed to load texture";
	}
	else
	{
		em.addTexture(name, t);
	}
}
 
int main()
{
	//Init entity manager
	EntityManager em;

	//Load assets-------------------------------------------------------

	//Load font for info
	sf::Font font;
	if (!font.loadFromFile("Courier Prime Code.ttf"))
	{
		cout << "Error: Failed to load font" << endl;
	}

	//Load font for score
	sf::Font lato;
	if (!lato.loadFromFile("Lato-Bold.ttf"))
	{
		cout << "Error: Failed to load font" << endl;
	}

	em.setFont(lato);
	//cout << em.getFont() << endl;
	//Load background
	sf::Texture grassTexture;
	if (!grassTexture.loadFromFile("grass.png"))
	{
		cout << "Error: Failed to load texture";
	}

	//load Textures and store in entity manager
	sf::Texture t;
	loadTexture(em, t, "Player.png", "Player");
	loadTexture(em, t, "Bullet.png", "Bullet");
	loadTexture(em, t, "zombiesheet.png", "Zombie");
	loadTexture(em, t, "Ammo.png", "Ammo");
	loadTexture(em, t, "Blood1.png", "Blood1");
	loadTexture(em, t, "Blood2.png", "Blood2");
	loadTexture(em, t, "Blood3.png", "Blood3");
	loadTexture(em, t, "Blood4.png", "Blood4");
	loadTexture(em, t, "Blood5.png", "Blood5");
	loadTexture(em, t, "Blood6.png", "Blood6");

	//Set background
	sf::Sprite grassBackground(grassTexture);

	//Other stuff-------------------------------------------------------

	//Randomize seed
	srand(time(0));

	//Set text
	sf::Text text;
	string s;
	text.setFont(font);
	text.setCharacterSize(13);
	text.setPosition(sf::Vector2f(5.0, 5.0));

	//Game init---------------------------------------------------------
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Topdown Shooter");
	//window.setFramerateLimit(60);
	bool quit = false;
	sf::Clock clock;
	
	//Spawn player and store it in the entity manager
	Player player(em);
	em.setPlayer(&player);

	//Spawn ammo and store it in the entity manager
	Ammo ammo(em);
	ammo.setActive(false);
	em.setAmmo(&ammo);

	//Spawn gamecontrol and store it in the entity manager
	GameControl gamecontrol(em);
	em.setGameControl(&gamecontrol);

	float fpsTimer = { 0.5f };
	int fps{ 0 };
	bool showInfo = false;

	//Game loop---------------------------------------------------------------------------------------
	while (!quit)
	{
		//Update clock
		auto delta = clock.restart();
		float deltaTime = (delta.asSeconds());
		//float deltaTime = (delta.asMicroseconds() / 1000000.0f);

		//Get the framerate every 0.5 second
		fpsTimer -= deltaTime;
		if (fpsTimer <= 0)
		{
			fps = 1.0f / deltaTime;
			fpsTimer = 0.5f;
		}

		//Update every entity
		if(window.hasFocus())
		{
		    em.update(em, deltaTime, window);
		}
		//Set text to be displayed in upper left corner
		stringstream ss;
		if (showInfo == true)
		{
			 ss << endl << endl << endl << "FPS: " << fps << endl
				<< "Player position (x, y) : " << em.getPlayer()->getPosition() << endl
				<< "Player speed (px/s)    : " << setw(6) << length(em.getPlayer()->getSpeed()) << endl
				<< "Mouse position         : " << sf::Mouse::getPosition(window) << endl
				<< "Mouse direction        : " << vectorAngle(em.getPlayer()->mouseDirection) << endl
				<< "Entities               : " << em.entityCount() << endl
				<< "Player ammo            : " << em.getPlayer()->getAmmo() << endl
				<< "Game state             : " << em.getGameControl()->getState() << endl
			    <<     "State timer            : " << em.getGameControl()->getStateTimer() << endl
			    <<     "Spawn timer            : " <<em.getGameControl()->getSpawnTimer() <<endl;
		}
		text.setString(ss.str());

		//Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				//Close window
			case sf::Event::Closed:
				quit = true;
				break;

				//Key Pressed
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					//Escape
				case sf::Keyboard::Escape:
					quit = true;
					break;

				case sf::Keyboard::I:
					showInfo = !showInfo;

				case sf::Keyboard::L:
					//em.getGameControl()->gameStart(em);
					//em.getPlayer()->setAlive(!em.getPlayer()->isAlive());
					break;

				case sf::Keyboard::P:
					//em.removePlayer();
					break;
				}
				break;
				
				//Other
			default:
				//cout << "Event: " << event.type << endl;
				break;
			}
		}	

		//Draw
		window.clear();

		window.draw(grassBackground);
		em.draw(window);
		//ammo.draw(window);
		window.draw(text);

		window.display();
	}
	//----------------------------------------------------------------------------------------------

	window.close();
	return 0;
}

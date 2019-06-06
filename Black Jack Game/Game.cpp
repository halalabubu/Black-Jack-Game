
#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game.h"
#include "GameState.h"



void Game::loadTextures()
{
	//texmgr.loadTexture("MainMenu", "Textures/Mainmenu.png");
}

void Game::pushState(GameState* state)
{
	states.push(state);
}

void Game::popState()
{
	delete states.top();
	states.pop();
}

void Game::changeState(GameState* state)
{
	if (states.empty()==true)
	{
		popState();
	}
	pushState(state);
}

GameState* Game::peekState()
{
	if (states.empty())
		return nullptr;
	return states.top();
}

void Game::gameLoop()
{
	sf::Clock clock;

	while ( window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		//float dt = elapsed.asMilliseconds();

		//if (peekState() == nullptr)		//TODO learn more
			//continue;
		peekState()->handleInput();
		peekState()->update(elapsed);
		window.clear();
		peekState()->draw(elapsed);
		window.display();
	}
}

Game::Game()
{
	 window.create(sf::VideoMode(384, 216), "Black Jack"); // make user defined or load from file (file would be better)
	 window.setFramerateLimit(144);
	 loadTextures();
	 window.setSize(sf::Vector2u(1280,720));
	 window.setPosition(sf::Vector2i(100,100));
}


Game::~Game()
{
	while (!states.empty()) popState();		//while not empty, pop
}

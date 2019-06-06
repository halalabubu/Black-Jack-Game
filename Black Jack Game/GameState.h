#pragma once

#include "Game.h"
#include<SFML/System/Time.hpp>



class GameState
{
public:
	Game* game;

	virtual void draw(const sf::Time dt) = 0;
	virtual void update(const sf::Time dt) = 0;
	virtual void handleInput() = 0;

};


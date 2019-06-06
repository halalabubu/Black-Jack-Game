#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Animation.h"


class MainMenu : public GameState
{
private:
	sf::View view; //if i need to adjust it
	sf::Sprite singleplay;
	sf::Sprite multiplay;

	sf::Sprite background;// bad way of doing things but for small scale itsa fine

	Animation *animatedmenu;
public:



	// redefining to meet needs
	virtual void draw(const sf::Time dt);
	virtual void update(const sf::Time dt);
	virtual void handleInput();


	MainMenu(Game* game);
	~MainMenu() { delete animatedmenu; }
};


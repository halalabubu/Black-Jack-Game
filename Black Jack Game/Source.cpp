//Jonathan Cookson
//Final Project for CIS 7
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "MainMenu.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
int main()
{
	Game game;

	game.pushState(new MainMenu(&game)); // copy bad so & == :)
	game.gameLoop();

	return 0;
}
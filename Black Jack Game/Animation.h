#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System/Time.hpp>
#include<vector>



class Animation
{
public:
	Animation(sf::Sprite& target, int tframelengthmill); // sf::sprite, framelength in milliseconds
	~Animation();

	void addframe(const sf::IntRect& frame);
	void update(const sf::Time & currenttime);

private:
	std::vector<sf::IntRect> tiles;
	//sf::Time leftovertime;
	sf::Sprite& target;
	int leftovertime;
	int framelengthmill;
	//sf::Time framelengthmill = sf::milliseconds(100);
	int currenttile;
};


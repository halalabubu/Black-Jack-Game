#include "Animation.h"



Animation::Animation(sf::Sprite& target, int tframelengthmill) :target(target)
{
	framelengthmill = tframelengthmill;
	currenttile = 0;
	leftovertime = 0;
};

Animation::~Animation()
{

}

void Animation::addframe(const sf::IntRect& frame)
{
	tiles.push_back(frame);
	target.setTextureRect(tiles[currenttile]);
}

void Animation::update(const sf::Time& elapsedtime)
{

	leftovertime += elapsedtime.asMilliseconds();

	if (leftovertime > framelengthmill)
	{
		currenttile++;
		leftovertime = leftovertime - framelengthmill;
		if (currenttile == tiles.size())
			currenttile = 0;
	}
	target.setTextureRect(tiles[currenttile]);
}

#pragma once

#include<SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "TextureManager.h"

struct Card
{
	std::vector<int> values; // will be one or two values (unless user made rules are used)
	bool flipped = false;
	std::string suite;//prob wont use
	sf::Sprite sprite;
};


class CardDeck
{
public:
	sf::Sprite backofcard;
	CardDeck(TextureManager& texmgr); //texturelocation, carddata
	~CardDeck();

	Card getCard();
	void shufflecards(); // shuffles the cards
	void setupcards();	
	std::vector<Card> cards;

private:

	std::string carddata;
	//int cardx;//pixels wide
	//int cardy;//pixels tall
};


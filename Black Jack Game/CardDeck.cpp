#include "CardDeck.h"
#include <algorithm>  
#include <fstream>
#include <vector>
#include <string>

#include<iostream> //testing purposes

//TODO offer multi deck options
CardDeck::CardDeck(TextureManager& texmgr)
{
	const int NUMBEROFCARDSSUITE = 13;
	Card card;
	texmgr.loadTexture("Cards", "Textures/Cards.png");
	texmgr.loadTexture("Backside", "Textures/Backofcard.png");
	backofcard.setTexture(texmgr.getRef("Backside"));


	////cards is the vector
	//std::ifstream din;
	//din.open("Data/carddata.txt"); // card data no error check lel
	//std::string temp;
	//std::vector<std::string> tokenized;

	//while (!din.eof())
	//{
	//	din >> temp;
	//	tokenized.push_back(temp);
	//}


	////find x
	////find y
	//for (size_t i = 0; i < tokenized.size(); i++)
	//{
	//	if (tokenized[i] == "<cardsize>")
	//	{
	//		cardx = std::stoi(tokenized[i + 2]);
	//		cardy = std::stoi(tokenized[i + 4]);
	//		break;
	//	}

	//}
	//hearts
	for (int i = 0; i < NUMBEROFCARDSSUITE; i++)
	{
		card.sprite.setTexture(texmgr.getRef("Cards"));
		card.sprite.setTextureRect(sf::IntRect(0 + 32 * i, 0, 32, 64));
		if (i + 1 == 1)
		{
			card.values.push_back(1);
			card.values.push_back(11);
		}
		else if (i + 1 > 9)
		{
			card.values.push_back(10);
		}
		else
		{
			card.values.push_back(i + 1);
		}
		card.suite = "Heart";
		cards.push_back(card);
		card.values.clear();
	}
	//clubs
	for (size_t i = 0; i < NUMBEROFCARDSSUITE; i++)
	{
		card.sprite.setTexture(texmgr.getRef("Cards"));
		card.sprite.setTextureRect(sf::IntRect(0 + 32 * i, 64, 32, 64));

		if (i + 1 == 1)
		{
			card.values.push_back(1);
			card.values.push_back(11);
		}
		else if (i + 1 > 9)
		{
			card.values.push_back(10);
		}
		else
		{
			card.values.push_back(i + 1);
		}

		card.suite = "Clubs";
		cards.push_back(card);
		card.values.clear();
	}
	//spades
	for (size_t i = 0; i < NUMBEROFCARDSSUITE; i++)
	{
		card.sprite.setTexture(texmgr.getRef("Cards"));
		card.sprite.setTextureRect(sf::IntRect(0 + 32 * i, 128, 32, 64));
		if (i + 1 == 1)
		{
			card.values.push_back(1);
			card.values.push_back(11);
		}
		else if (i + 1 > 9)
		{
			card.values.push_back(10);
		}
		else
		{
			card.values.push_back(i + 1);
		}
		card.suite = "Spades";
		cards.push_back(card);
		card.values.clear();
	}
	//diamonds
	for (size_t i = 0; i < NUMBEROFCARDSSUITE; i++)
	{
		card.sprite.setTexture(texmgr.getRef("Cards"));
		card.sprite.setTextureRect(sf::IntRect(0 + 32 * i, 192, 32, 64));
		if (i + 1 == 1)
		{
			card.values.push_back(1);
			card.values.push_back(11);
		}
		else if (i + 1 > 9)
		{
			card.values.push_back(10);
		}
		else
		{
			card.values.push_back(i + 1);
		}
		card.suite = "Diamonds";
		cards.push_back(card);
		card.values.clear();
	}




	//for (size_t i = 0; i < cards.size(); i++)
	//{
	//	std::cout << cards[i].values[0] << std::endl;
	//	std::cout << cards[i].suite << std::endl;
	//}

}

CardDeck::~CardDeck()
{
}

Card CardDeck::getCard()
{
	Card temp;
	temp = cards.back();
	cards.pop_back();
	return temp;
}

void CardDeck::shufflecards() // shuffles the cards
{
	std::srand(time(0)); // twelve starts with ace
	std::random_shuffle(cards.begin(), cards.end());
}

void CardDeck::setupcards()
{
}

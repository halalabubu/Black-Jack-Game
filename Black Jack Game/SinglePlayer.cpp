#include "SinglePlayer.h"
#include <iostream>

void SinglePlayer::draw(const sf::Time dt)
{
	//this->game->window.clear(sf::Color::Red);




	this->game->window.draw(background);
	for (size_t i = 0; i < playerCards.size(); i++)
	{
		playerCards[i].sprite.setPosition(sf::Vector2f(0 + 40 * i, 152));
		this->game->window.draw(playerCards[i].sprite);
	}
	for (size_t i = 0; i < dealerCards.size(); i++)
	{
		dealerCards[i].sprite.setPosition(sf::Vector2f(0 + 40 * i, 0));
		this->game->window.draw(dealerCards[i].sprite);
	}
	if (turnNumber == 2)
	{
		this->game->window.draw(cards.backofcard);
	}


	if (turnNumber < 3)
	{

		this->game->window.draw(hit);
		this->game->window.draw(stay);
		if (cardDrawn == false)
		{
			this->game->window.draw(betDouble);
			this->game->window.draw(surrender);
		}

	}
	if (turnNumber == 4)
	{
		this->game->window.draw(losewin);
		this->game->window.draw(reset);
		this->game->window.draw(dealerScoreText);
	}

	this->game->window.draw(playerScoreText);

	this->game->window.draw(playerCashText);
}

void SinglePlayer::update(const sf::Time dt)
{
	if (turnNumber == 1) // set up
	{
		playerDraw();
		dealerDraw();
		turnNumber++;
	}
	else if (turnNumber == 2)
	{
		if (playerScore == 21 && playerCards.size() == 2)
		{
			turnNumber = 4;
			blackjack = true;
		}

	}
	else if (turnNumber == 3) // 2 is player turn but simple handled in handelInput
	{
		dealerAi();
		turnNumber++;
	}
	else if (turnNumber > 3)
	{
		if (dealerScore > playerScore && dealerScore < 22)
		{
			drawLose();
			won = false;
		}
		else if (playerScore > dealerScore && playerScore < 22)
		{
			drawWin();
			won = true;
		}
		else if (dealerScore > 21 && playerScore < 22)
		{
			drawWin();
			won = true;
		}
		else if (playerScore == dealerScore)
		{
			drawTie();
			tie = true;
		}
		else if (playerScore > 21)
		{
			drawLose();
			won = false;
		}
	}
	//TODO insta win if you have ace and face

	updateCash();
}

void SinglePlayer::handleInput()
{
	sf::Event event;
	hit.setColor(sf::Color(255, 255, 255));
	stay.setColor(sf::Color(255, 255, 255));
	reset.setColor(sf::Color(255, 255, 255));
	betDouble.setColor(sf::Color(255, 255, 255));
	surrender.setColor(sf::Color(255, 255, 255));

	for (size_t i = 0; i < playerCards.size(); i++)
	{
		playerCards[i].sprite.setColor(sf::Color(255, 255, 255));
	}

	// get the current mouse position in the window
	sf::Vector2i pixelPos = sf::Mouse::getPosition(game->window);
	// convert it to world coordinates
	sf::Vector2f worldPos = game->window.mapPixelToCoords(pixelPos);



	if (hit.getGlobalBounds().contains(worldPos))
		hit.setColor(sf::Color(200, 100, 0));
	else if (stay.getGlobalBounds().contains(worldPos))
		stay.setColor(sf::Color(200, 100, 0));
	else if (reset.getGlobalBounds().contains(worldPos))
		reset.setColor(sf::Color(200, 100, 0));
	else if (betDouble.getGlobalBounds().contains(worldPos))
		betDouble.setColor(sf::Color(200, 100, 0));
	else if (surrender.getGlobalBounds().contains(worldPos))
		surrender.setColor(sf::Color(200, 100, 0));



	for (size_t i = 0; i < playerCards.size(); i++) // bad code for the win :) grid would be better but its good enough
	{
		if (playerCards[i].sprite.getGlobalBounds().contains(worldPos))
			playerCards[i].sprite.setColor(sf::Color(200, 100, 0));
	}



	while (this->game->window.pollEvent(event))
	{

		//button logic
		if (event.type == sf::Event::MouseButtonPressed)// left click...
		{
			if (hit.getGlobalBounds().contains(worldPos))
			{
				cardDrawn = true;
				playerDraw();
				//turnNumber++;
			}
			else if (stay.getGlobalBounds().contains(worldPos))
			{
				turnNumber++; //TODO do something good now?
			}
			else if (reset.getGlobalBounds().contains(worldPos))
			{
				resetGame(); //TODO do something good now?
			}
			else if (betDouble.getGlobalBounds().contains(worldPos))
			{
				cardDrawn = true;//shhhhhh you didnt see this
				betDoubleCash();
				playerDraw();
				turnNumber++;
			}
			else if (surrender.getGlobalBounds().contains(worldPos))
			{
				surrendered = true;
				surrenderRound();
			}










			for (size_t i = 0; i < playerCards.size(); i++)
			{
				if (playerCards[i].sprite.getGlobalBounds().contains(worldPos) && playerCards[i].values[0] == 1)
				{
					if (playerCards[i].flipped == false)
					{
						playerScore += 10; //TODO make reversable
						playerCards[i].flipped = true;
					}
					else
					{
						playerCards[i].flipped = false;
						playerScore -= 10;
					}

					updateScores();
				}
			}
		}

		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
		{
			this->game->window.close();
			break;
		}
		/* Resize the window */
		case sf::Event::Resized:
		{
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape) this->game->window.close();
			break;
		}
		default: break;
		}




	}

	return;
}

SinglePlayer::SinglePlayer(Game* game) : cards(game->texmgr)
{
	this->game = game;

	surrendered = false;
	won = false;
	tie = false;
	blackjack = false;
	cardDrawn = false;
	betSize = 10;
	playerCash = 100;
	dealerScore = 0;
	playerScore = 0;
	cards.backofcard.setPosition(40, 0);
	cards.shufflecards();

	this->game->texmgr.loadTexture("playbuttons", "Textures/playbuttons.png");
	this->game->texmgr.loadTexture("backgroundgame", "Textures/backgroundgame.png");
	this->game->texmgr.loadTexture("losewin", "Textures/losewin.png");

	losewin.setTexture(this->game->texmgr.getRef("losewin"));
	hit.setTexture(this->game->texmgr.getRef("playbuttons"));
	stay.setTexture(this->game->texmgr.getRef("playbuttons"));
	reset.setTexture(this->game->texmgr.getRef("playbuttons"));
	surrender.setTexture(this->game->texmgr.getRef("playbuttons"));
	betDouble.setTexture(this->game->texmgr.getRef("playbuttons"));
	background.setTexture(this->game->texmgr.getRef("backgroundgame"));
	hit.setTextureRect(sf::IntRect(0, 0, 32, 16));	//TODO could implement file load way( too much work though :/ )
	stay.setTextureRect(sf::IntRect(32, 0, 32, 16));
	reset.setTextureRect(sf::IntRect(64, 0, 32, 16));
	betDouble.setTextureRect(sf::IntRect(0, 16, 32, 16));
	surrender.setTextureRect(sf::IntRect(32, 16, 32, 16));

	//position never changes 
	hit.setPosition(32, 100);
	stay.setPosition(32 * 2 + 10, 100);
	betDouble.setPosition(32 * 3 + 10 * 2, 100);
	surrender.setPosition(32 * 4 + 10 * 3, 100);


	reset.setPosition(192 - 16, 216 - 32);

	cash = 50; //starting cash
	//cards.shufflecards();
	turnNumber = 1;


	font.loadFromFile("Font/font.ttf");
	playerCashText.setFont(font);
	dealerScoreText.setFont(font);
	playerScoreText.setFont(font);
	playerCashText.setCharacterSize(13);
	playerScoreText.setCharacterSize(13);
	dealerScoreText.setCharacterSize(13);
	playerCashText.setPosition(250, 125);
	dealerScoreText.setPosition(5, 74);
	playerScoreText.setPosition(5, 125);
	playerCashText.setFillColor(sf::Color::Black);
	playerScoreText.setFillColor(sf::Color::Black);
	dealerScoreText.setFillColor(sf::Color::Black);

}

void SinglePlayer::dealerDraw()
{
	//dealerScore = 0;
	if (turnNumber == 1)	//TODO fix the showing dealer points
	{
		dealerCards.push_back(cards.getCard());
		dealerCards.push_back(cards.getCard());
		dealerScore = dealerCards[0].values[0];
		dealerScore += dealerCards[1].values[0];
	}
	else
	{
		dealerCards.push_back(cards.getCard());
		dealerScore += dealerCards.back().values[0];
	}
	updateScores();
	std::cout << "Cards Left: " << cards.cards.size() << std::endl;

}

void SinglePlayer::playerDraw()
{
	if (turnNumber == 1)
	{
		//playerScore = 0;
		playerCards.push_back(cards.getCard()); // card 1
		playerCards.push_back(cards.getCard()); // card 2
		playerScore = playerCards[0].values[0];
		playerScore += playerCards[1].values[0];
	}
	else
	{
		playerCards.push_back(cards.getCard());
		playerScore += playerCards.back().values[0];
	}
	updateScores();
	std::cout << "Cards Left: " << cards.cards.size() << std::endl;
}

void SinglePlayer::updateScores()
{
	//update player score
	playerScoreText.setString("Player score: " + std::to_string(playerScore));
	//update dealer score
	dealerScoreText.setString("Dealer score: " + std::to_string(dealerScore));
}

void SinglePlayer::resetGame()
{
	if (tie == true)
	{
		//do nothing
	}
	else if (blackjack == true)
	{
		playerCash = playerCash + betSize * 3;
	}
	else if (surrendered == true)
	{
		playerCash = playerCash - betSize / 2;
	}
	else if (won == true)
	{
		playerCash += betSize;
	}
	else
	{
		playerCash -= betSize;
	}
	cardDrawn = false;
	surrendered = false;
	won = false;
	tie = false;
	blackjack = false;
	betSize = 10;
	playerCards.clear();
	dealerCards.clear();
	turnNumber = 1;
	playerScore = 0;
	dealerScore = 0;
}

void SinglePlayer::dealerAi()
{
	int scorechoice1 = 0;
	int scorechoice2 = 0;
	bool flippedOnce = false;
	//duplicated, i know
	flippedOnce == false; //reset
	scorechoice1 = 0;
	scorechoice2 = 0;
	for (size_t i = 0; i < dealerCards.size(); i++) // dont have to rescan but meh, easier
	{
		scorechoice1 += dealerCards[i].values[0];
	}
	for (size_t i = 0; i < dealerCards.size(); i++)
	{
		if (dealerCards[i].values[0] == 1 && flippedOnce == false)
		{
			scorechoice2 += 11;
			flippedOnce == true;
		}
		else
			scorechoice2 += dealerCards[i].values[0];
	}
	while (scorechoice1 < 22 || scorechoice2 < 22)
	{



		if (scorechoice1 < 17 || scorechoice2 < 17)
		{
			dealerDraw();
		}

		scorechoice1 = 0;
		scorechoice2 = 0;
		flippedOnce == false; //reset
		for (size_t i = 0; i < dealerCards.size(); i++) // dont have to rescan but meh, easier
		{
			scorechoice1 += dealerCards[i].values[0];
		}
		for (size_t i = 0; i < dealerCards.size(); i++)
		{
			if (dealerCards[i].values[0] == 1 && flippedOnce == false)
			{
				scorechoice2 += 11;
				flippedOnce == true;
			}
			else
			{
				scorechoice2 += dealerCards[i].values[0];
			}
		}


		if (scorechoice1 > 16 && scorechoice1 < 22)
		{
			if (scorechoice1 > scorechoice2 && scorechoice2 < 21)
			{
				dealerScore = scorechoice1;
				break;
			}
			if (scorechoice2 > 21)
			{
				dealerScore = scorechoice1;
				break;
			}

		}
		if (scorechoice2 > 16 && scorechoice2 < 22)
		{
			if (scorechoice2 > scorechoice1 && scorechoice1 < 21)
			{
				dealerScore = scorechoice2;
				break;
			}
			if (scorechoice1 > 21)
			{
				dealerScore = scorechoice2;
				break;
			}

		}
		if (scorechoice1 > 16 && scorechoice1 == scorechoice2)
		{
			break;
		}
	}
	updateScores();

}

void SinglePlayer::updateCash()
{
	//update player cash
	playerCashText.setString("Cash: $" + std::to_string(playerCash));
}

void SinglePlayer::betDoubleCash()
{
	betSize = betSize * 2;
}

void SinglePlayer::surrenderRound()
{
	resetGame();
}

void SinglePlayer::outOfCards()
{
	if (cards.cards.empty() == true)
	{
		game->popState();
	}
}


//TODO setting rect everytime not effecient but whatevs
void SinglePlayer::drawLose()
{
	losewin.setTextureRect(sf::IntRect(0, 0, 384, 216));
	this->game->window.draw(losewin);
}
void SinglePlayer::drawWin()
{
	losewin.setTextureRect(sf::IntRect(0 + 384, 0, 384, 216));
	this->game->window.draw(losewin);
}
void SinglePlayer::drawTie()
{
	losewin.setTextureRect(sf::IntRect(0 + 384 * 2, 0, 384, 216));
	this->game->window.draw(losewin);
}


SinglePlayer::~SinglePlayer()
{

}

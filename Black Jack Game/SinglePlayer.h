#pragma once
#include "GameState.h"
#include "Animation.h"
#include "CardDeck.h"

class SinglePlayer : public GameState
{
private:
	CardDeck cards;
	std::vector<Card> playerCards;
	std::vector<Card> dealerCards;
	int cash;	//TODO display cash top right
	int turnNumber;
	int playerScore;
	int dealerScore;
	int playerCash;
	int betSize;
	bool won;
	bool tie;
	bool blackjack;
	bool surrendered;
	bool cardDrawn;

	sf::Font font;
	sf::Text playerScoreText;
	sf::Text dealerScoreText;
	sf::Text playerCashText;

	sf::View view; //if i need to adjust it
	//buttons
	sf::Sprite hit;
	sf::Sprite stay;
	sf::Sprite reset;
	sf::Sprite losewin;
	sf::Sprite betDouble;
	sf::Sprite surrender;

	sf::Sprite background;// bad way of doing things but for small scale itsa fine
	void dealerDraw();
	void playerDraw();
	void updateScores();
	void resetGame();
	void dealerAi();
	void updateCash();

	void betDoubleCash();
	void surrenderRound();
	void outOfCards();

	void drawWin();
	void drawLose();
	void drawTie();
	//Animation* animatedmenu;
public:


	// redefining to meet needs
	virtual void draw(const sf::Time dt);
	virtual void update(const sf::Time dt);
	virtual void handleInput();

	SinglePlayer(Game* game);
	~SinglePlayer();
};


#include "MainMenu.h"
#include "SinglePlayer.h"

void MainMenu::draw(const sf::Time dt)//TODO change to reference?
{


	//this->game->window.clear(sf::Color::Black);

	//this->game->window.setView(view); // not needed
	//draw menu
	this->game->window.draw(background);
	//draw buttons
	this->game->window.draw(singleplay);
	this->game->window.draw(multiplay);
}

void MainMenu::update(const sf::Time dt)
{
	animatedmenu->update(dt);
}

void MainMenu::handleInput()
{
	//background.setTexture(this->game->texmgr.getRef("Mainmenu"));
	sf::Event event;
	//TODO fix this shit, make custom button class so i can easily create buttons
	singleplay.setColor(sf::Color(255, 255, 255));
	multiplay.setColor(sf::Color(255, 255, 255));
	// get the current mouse position in the window
	sf::Vector2i pixelPos = sf::Mouse::getPosition(game->window);
	// convert it to world coordinates
	sf::Vector2f worldPos = game->window.mapPixelToCoords(pixelPos);


	//TODO fix ugly code LOW priority
	//button logic
	if (singleplay.getGlobalBounds().contains(worldPos))
	{
		singleplay.setColor(sf::Color(200, 100, 0));
	}
	if (multiplay.getGlobalBounds().contains(worldPos))
	{
		multiplay.setColor(sf::Color(200, 100, 0));
	}

	while (this->game->window.pollEvent(event))
	{
		//button logic
		if (singleplay.getGlobalBounds().contains(worldPos))
		{
			singleplay.setColor(sf::Color(200, 100, 0));
			if (event.type == sf::Event::MouseButtonPressed)// left click...
			{
				//TODO change state here
				game->changeState(new SinglePlayer(game));
			}
		}
		if (multiplay.getGlobalBounds().contains(worldPos))
		{
			multiplay.setColor(sf::Color(200, 100, 0));
		}







		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
		{
			game->window.close();
			break;
		}
		/* Resize the window */
		case sf::Event::Resized:
		{
			//this->view.setSize(event.size.width, event.size.height);
			//background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0)));
			//background.setScale(
			//	float(event.size.width) / float(background.getTexture()->getSize().x),
			//	float(event.size.height) / float(background.getTexture()->getSize().y));
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

MainMenu::MainMenu(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);

	this->game->texmgr.loadTexture("MainMenu", "Textures/MainMenu.png");
	this->game->texmgr.loadTexture("Buttons", "Textures/Menubuttons.png");
	this->background.setTexture(this->game->texmgr.getRef("MainMenu"));
	singleplay.setTexture(this->game->texmgr.getRef("Buttons"));
	multiplay.setTexture(this->game->texmgr.getRef("Buttons"));

	// too lazy to setup properly ie button class and stuff
	singleplay.setTextureRect(sf::IntRect(0, 0, 128, 32));
	multiplay.setTextureRect(sf::IntRect(128, 0, 128, 32));
	singleplay.setPosition(16, 16);
	multiplay.setPosition(240, 16);

	animatedmenu = new Animation(background, 100);// TODO make animation class more robust
	for (size_t i = 0; i < 8; i++) // 8 tiles long frame is 
	{
		animatedmenu->addframe(sf::IntRect(0 + 384 * i, 0, 384, 216));
	}
}

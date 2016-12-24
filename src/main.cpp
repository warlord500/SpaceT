#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>
#include "main.h"

const int THE_MEANING_OF_LIFE_THE_UNIVERSE_AND_EVERYTHING = 42;

int main()
{
	Game game;
	game.gameLoop();

	return THE_MEANING_OF_LIFE_THE_UNIVERSE_AND_EVERYTHING;
}

//                                               260 x 480 is a good size for Tetris
Game::Game() : tetrisManager(sf::FloatRect(0, 0, 260, 480)), screenRectSpaceInv(400, 50,624,579), playMan(images,screenRectSpaceInv)
{
	window.create(sf::VideoMode(screenWidth, screenHeight), "Space Tetris");
	window.setFramerateLimit(30);
}

Game::~Game()
{

}

void Game::gameLoop()
{
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window : exit
			switch(event.type)
			{
			case sf::Event::KeyPressed:
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		// Collects data on the buttons pressed and reports to the Tetris manager
		tetrisInputs.buttons.moveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		tetrisInputs.buttons.moveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		tetrisInputs.buttons.rotateRight = sf::Keyboard::isKeyPressed(sf::Keyboard::X);
		tetrisInputs.buttons.rotateLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
		tetrisInputs.buttons.drop = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
		tetrisInputs.buttons.quickDrop = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		tetrisInputs.buttons.hold = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

		window.clear(sf::Color::Black);
		tetrisOutputs = tetrisManager.play(window, tetrisInputs);
		assert(tetrisOutputs.gameOver == false); // Insert inter-game logic here

		playMan.update(window, screenRectSpaceInv);

		window.display();
	}
}

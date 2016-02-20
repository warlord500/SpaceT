#include <SFML/Graphics.hpp>
#include <main.h>
#include <iostream>
#include <assert.h>

int main()
{
    Game game;
    game.gameLoop();

    return 0;
}

Game::Game() : tetrisManager(screenHeight, screenWidth)
{
	window.create(sf::VideoMode(screenWidth, screenHeight), "Space Tetris");
	//if(!images.addAllCommonTextures())
        //false; // Throw an exception or something


   // enemyManager eneMan(images,screenRectSpaceInv);
            //the size of screen playing in.)
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
			case sf::Event::Closed:
				window.close();
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

        window.clear(sf::Color::Cyan);
		tetrisOutputs = tetrisManager.playTetris(window, tetrisInputs);
		assert(tetrisOutputs.gameOver == false);

        // remove from code because playermanager will replace the need for it.
        //eneMan.update(window);
        //playMan.update(window,screenRectSpaceInv);
        // Update the window
        window.display();
    }
}

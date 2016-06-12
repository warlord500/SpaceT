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

Game::Game() : tetrisManager(screenHeight, screenWidth), screenRectSpaceInv(400, 50,624,579), playMan(images,screenRectSpaceInv)
{
	window.create(sf::VideoMode(screenWidth, screenHeight), "Space Tetris");
	window.setFramerateLimit(30);
	//if(!images.addAllCommonTextures())
	  //  throw 0; // Throw an exception or something


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
            default :
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

        window.clear(sf::Color::Black);
		tetrisOutputs = tetrisManager.play(window, tetrisInputs);
		assert(tetrisOutputs.gameOver == false); // Insert inter-game logic here

        playMan.update(window,screenRectSpaceInv);
        window.display();
    }
}

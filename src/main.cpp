#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <space_invaders/textureManager.h>
//#include <space_invaders/enemyManager.h>
#include <space_invaders/spaceInvManager.h>
#include <tetris/tetrisGameManager.h>
#include <main.h>

int main()
{
    Game game;
    game.gameLoop();
    return EXIT_SUCCESS;
}

Game::Game()
{
	window.create(sf::VideoMode(screenWidth, screenHeight), "Space Tetris");
	if(!images.addAllCommonTextures())
        false; // Throw an exception or something
	sf::FloatRect screenRectSpaceInv(tetrisGameManager::getTetrisGameSize().x,0,
		screenWidth - tetrisGameManager::getTetrisGameSize().x,screenHeight);
    spaceInvManager playMan(images,screenRectSpaceInv);
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
                default:
                    break;
                }
        }

        // Clear screen
        window.clear(sf::Color::Black);

        // Draw tetris grid
        gameManager.updateGrid(window);
        // remove from code because playermanager will replace the need for it.
        //eneMan.update(window);
        playMan.update(window,screenRectSpaceInv);
        // Update the window
        window.display();
    }
}

#include <SFML/Graphics.hpp>
#include <main.h>

int main()
{
    Game game;
    game.gameLoop();

    return 0;
}

Game::Game() : screenRectSpaceInv(screenWidth / 2, 0, screenWidth, screenHeight), playMan(images,screenRectSpaceInv)
{
	window.create(sf::VideoMode(screenWidth, screenHeight), "Space Tetris");
	if(!images.addAllCommonTextures())
        false; // Throw an exception or something


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
        tetrisManager.updateGrid(window);
        // remove from code because playermanager will replace the need for it.
        //eneMan.update(window);
        playMan.update(window,screenRectSpaceInv);
        // Update the window
        window.display();
    }
}

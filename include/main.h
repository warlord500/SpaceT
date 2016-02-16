#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <tetris/tetrisGameManager.h>

const int screenWidth = 1020;
const int screenHeight = 696;

class Game
{
public:
	Game();
	~Game();
	void gameLoop();
private:
	sf::RenderWindow window;
	tetrisGameManager gameManager;
    textureManager images;
};

#endif

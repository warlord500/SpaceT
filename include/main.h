#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <space_invaders/spaceInvManager.h>
#include <space_invaders/textureManager.h>
#include <tetris/Manager.h>

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
	Tetris::GameManager tetrisManager;
	Tetris::Inputs tetrisInputs;
	Tetris::Outputs tetrisOutputs;
	//spaceInvManager playMan;
    //textureManager images;
    //sf::FloatRect screenRectSpaceInv;
};

#endif

#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <space_invaders/spaceInvManager.h>
#include <space_invaders/textureManager.h>
#include <tetris/Manager.h>

const int screenWidth = 1020;
const int screenHeight = 696;
//object oriented wrapper around the global variables
//of the game
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
	sf::FloatRect screenRectSpaceInv; //this is the position data for the space invaders screen side
	SpaceInvaders::textureManager images;
	SpaceInvaders::spaceInvManager playMan;
};

#endif

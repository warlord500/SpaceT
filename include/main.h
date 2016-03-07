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
	//textureManager images; 
	//spaceInvManager playMan(images);
	//sf::FloatRect screenRectSpaceInv(0,300,400,500);
	//this is for setting the position of the games so they dont overlap
	//and look awful
};

#endif

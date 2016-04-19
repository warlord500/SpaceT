#include <iostream>
#include <SFML/Graphics.hpp>
#include <tetris/Manager.h>
#include <tetris/Renderer.h>
#include <tetris/Enums.h>

using namespace Tetris;

GameManager::GameManager(int windowHeight, int windowWidth)
	: renderer(windowHeight, windowWidth)
{
    tetriminoIsInPlay = true;
    tetriminoInPlay = new Tetrimino(random_shape);
    nextTetrimino = new Tetrimino(random_shape);

    wasPressed.moveLeft = false;
    wasPressed.moveRight = false;
    wasPressed.rotateRight = false;
    wasPressed.rotateLeft = false;
    wasPressed.drop = false;
    wasPressed.quickDrop = false;

    outputs.gameOver = false;

	dropTime = INITIAL_DROP_TIME;
    isStuck = false;
}

GameManager::~GameManager()
{
	delete tetriminoInPlay;
	delete nextTetrimino;
}

bool GameManager::manageButtonDelay(sf::Clock& timer, const bool isPressed, bool& wasPressed)
{
    //if delay on button has passed do work
    if(isPressed && (!wasPressed || timer.getElapsedTime().asMilliseconds() >= BUTTON_HOLD_DELAY))
    {
        timer.restart();
        wasPressed = true;
        return true;
    }
    if(!isPressed)
        wasPressed = false;
    return false;
}

void GameManager::manageButtonDelays(Buttons &rawButtons)
{
    rawButtons.moveLeft = manageButtonDelay(moveLeftTimer, rawButtons.moveLeft, wasPressed.moveLeft);
    rawButtons.moveRight = manageButtonDelay(moveRightTimer, rawButtons.moveRight, wasPressed.moveRight);
    rawButtons.rotateRight = manageButtonDelay(rotateRightTimer, rawButtons.rotateRight, wasPressed.rotateRight);
    rawButtons.rotateLeft = manageButtonDelay(rotateLeftTimer, rawButtons.rotateLeft, wasPressed.rotateLeft);
    rawButtons.drop = manageButtonDelay(dropTimer, rawButtons.drop, wasPressed.drop);
    rawButtons.quickDrop = manageButtonDelay(quickDropTimer, rawButtons.quickDrop, wasPressed.quickDrop);
}

Outputs GameManager::play(sf::RenderWindow& window, Inputs inputs)
{
    if(!tetriminoIsInPlay)
    {
    	tetriminoInPlay = nextTetrimino;
        nextTetrimino = new Tetrimino(random_shape);
        tetriminoIsInPlay = true;
        autoDropTimer.restart();
        isStuck = false;
    }

    manageButtonDelays(inputs.buttons);

    if(inputs.buttons.quickDrop)
    {
        do
        {
            tetriminoInPlay->moveDown();
        }
        while(gameBoard.tetriminoFit(*tetriminoInPlay));
        tetriminoInPlay->moveUp();
        gameBoard.addTetriminoToWell(*tetriminoInPlay);
        isStuck = true;
        autoDropTimer.restart();
    }
    else if(inputs.buttons.drop || autoDropTimer.getElapsedTime().asMilliseconds() >= dropTime)
    {
        tetriminoInPlay->moveDown();
        if(!gameBoard.tetriminoFit(*tetriminoInPlay))
        {
            tetriminoInPlay->moveUp();
            gameBoard.addTetriminoToWell(*tetriminoInPlay);
            isStuck = true;
        }
        autoDropTimer.restart();
    }
    if(!isStuck)
    {
        if(inputs.buttons.moveLeft)
        {
            tetriminoInPlay->moveLeft();
            if(!gameBoard.tetriminoFit(*tetriminoInPlay))
                tetriminoInPlay->moveRight();
        }
        else if(inputs.buttons.moveRight)
        {
            tetriminoInPlay->moveRight();
            if(!gameBoard.tetriminoFit(*tetriminoInPlay))
                tetriminoInPlay->moveLeft();
        }
        if(inputs.buttons.rotateRight)
        {
            tetriminoInPlay->rotateRight();
            if(!gameBoard.tetriminoFit(*tetriminoInPlay))
                tetriminoInPlay->rotateLeft();
        }
        else if(inputs.buttons.rotateLeft)
        {
            tetriminoInPlay->rotateLeft();
            if(!gameBoard.tetriminoFit(*tetriminoInPlay))
                tetriminoInPlay->rotateRight();
        }
    }
    gameBoard.clearFullRows();
	renderer.drawNextText(window);
	renderer.drawWell(window, gameBoard);
    renderer.drawTetrimino(window, *tetriminoInPlay);
    renderer.drawTetrimino(window, *nextTetrimino, true);
    if(isStuck)
    {
    	if(gameBoard.tetriminoInStaging(*tetriminoInPlay))
		{
			renderer.drawGameOverText(window);
			outputs.gameOver = true;
		}
		else
		{
			delete tetriminoInPlay;
			tetriminoIsInPlay = false;
			dropTime--;
		}
    }
    return outputs;
}

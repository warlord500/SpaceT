#include <iostream>
#include <SFML/Graphics.hpp>
#include "tetris/Manager.h"
#include "tetris/Renderer.h"
#include "tetris/Enums.h"

using namespace Tetris;

GameManager::GameManager(sf::FloatRect screenRect)
	: renderer(screenRect)
{
	tetriminoIsInPlay = true;
	hasHeld = false;
	tetriminoInPlay = new Tetrimino(random_shape);
	nextTetrimino = new Tetrimino(random_shape);
	holdTetrimino = NULL;

	wasPressed.moveLeft = false;
	wasPressed.moveRight = false;
	wasPressed.rotateRight = false;
	wasPressed.rotateLeft = false;
	wasPressed.drop = false;
	wasPressed.quickDrop = false;

	outputs.gameOver = false;

	dropTime = INITIAL_DROP_TIME;
	isStuck = false;
	score = 0;
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
	rawButtons.hold = manageButtonDelay(holdTimer, rawButtons.hold, wasPressed.hold);
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

	if(inputs.buttons.hold && !hasHeld)
	{
		// Resets the Tetrimino's position to default
		// It also needs to reset its rotation...
		tetriminoInPlay->setLocation(nextTetrimino->getLocation());
		tetriminoInPlay->resetRotation();

		if(holdTetrimino == NULL)
		{
			holdTetrimino = tetriminoInPlay;
			tetriminoIsInPlay = false;
		}
		else
		{
			Tetrimino *tempTetrimino;
			tempTetrimino = holdTetrimino;
			holdTetrimino = tetriminoInPlay;
			tetriminoInPlay = tempTetrimino;
		}
		hasHeld = true;
	}
	else if(inputs.buttons.quickDrop)
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
	score += gameBoard.clearFullRows() * 10;
	renderer.drawNextText(window);
	renderer.drawHoldText(window);
	renderer.drawWell(window, gameBoard);
	renderer.drawInPlay(window, *tetriminoInPlay);
	renderer.drawNext(window, *nextTetrimino);
	if(holdTetrimino != NULL)
		renderer.drawHold(window, *holdTetrimino);
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
			hasHeld = false;
		}
	}
	return outputs;
}

#include <SFML/Graphics.hpp>
#include <tetris/TetrisManager.h>
#include <tetris/Renderer.h>
#include <tetris/Enums.h>

tetrisGameManager::tetrisGameManager(int windowHeight, int windowWidth)
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

    tetrisOutputs.gameOver = false;

    isStuck = false;
}

tetrisGameManager::~tetrisGameManager()
{
	delete tetriminoInPlay;
	delete nextTetrimino;
}

bool tetrisGameManager::manageButtonDelay(sf::Clock& timer, const bool isPressed, bool& wasPressed)
{
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

void tetrisGameManager::manageButtonDelays(TetrisButtons& rawButtons)
{
    rawButtons.moveLeft = manageButtonDelay(moveLeftTimer, rawButtons.moveLeft, wasPressed.moveLeft);
    rawButtons.moveRight = manageButtonDelay(moveRightTimer, rawButtons.moveRight, wasPressed.moveRight);
    rawButtons.rotateRight = manageButtonDelay(rotateRightTimer, rawButtons.rotateRight, wasPressed.rotateRight);
    rawButtons.rotateLeft = manageButtonDelay(rotateLeftTimer, rawButtons.rotateLeft, wasPressed.rotateLeft);
    rawButtons.drop = manageButtonDelay(dropTimer, rawButtons.drop, wasPressed.drop);
    rawButtons.quickDrop = manageButtonDelay(quickDropTimer, rawButtons.quickDrop, wasPressed.quickDrop);
}

TetrisOutputs tetrisGameManager::playTetris(sf::RenderWindow& window, TetrisInputs inputs)
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
    else if(inputs.buttons.drop || autoDropTimer.getElapsedTime().asMilliseconds() >= AUTO_DROP_TIMER)
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

	renderer.drawWell(window, gameBoard);
    renderer.drawTetrimino(window, *tetriminoInPlay);
    renderer.drawTetrimino(window, *nextTetrimino, true);
    if(isStuck)
    {
    	if(gameBoard.tetriminoInStaging(*tetriminoInPlay))
		{
			tetrisOutputs.gameOver = true;
		}
		else
		{
			delete tetriminoInPlay;
			tetriminoIsInPlay = false;
		}
    }
    return tetrisOutputs;
}

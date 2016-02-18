#include <tetris/TetrisManager.h>
#include <SFML/Graphics.hpp>
#include <tetris/Enums.h>
#include <iostream>

tetrisGameManager::tetrisGameManager(int windowHeight, int windowWidth) : WINDOW_HEIGHT(windowHeight), WINDOW_WIDTH(windowWidth)
{
    tetriminoIsInPlay = false;
    wasPressed.moveLeft = false;
    wasPressed.moveRight = false;
    wasPressed.rotateRight = false;
    wasPressed.rotateLeft = false;
    wasPressed.drop = false;
    wasPressed.quickDrop = false;
}

void tetrisGameManager::setSfmlColors(sf::RectangleShape& toBeColored, const BlockColors color)
{
    switch(color)
    {
    case Cyan:
        toBeColored.setFillColor(sf::Color::Cyan);
        toBeColored.setOutlineColor(sf::Color(96, 216, 220));
        break;
    case Yellow:
        toBeColored.setFillColor(sf::Color::Yellow);
        toBeColored.setOutlineColor(sf::Color(222, 222, 79));
        break;
    case Orange:
        toBeColored.setFillColor(sf::Color(255, 166, 31));
        toBeColored.setOutlineColor(sf::Color(192, 124, 22));
        break;
    case Blue:
        toBeColored.setFillColor(sf::Color::Blue);
        toBeColored.setOutlineColor(sf::Color(23, 19, 138));
        break;
    case Green:
        toBeColored.setFillColor(sf::Color::Green);
        toBeColored.setOutlineColor(sf::Color(42, 183, 37));
        break;
    case Red:
        toBeColored.setFillColor(sf::Color::Red);
        toBeColored.setOutlineColor(sf::Color(195, 25, 30));
        break;
    case Purple:
        toBeColored.setFillColor(sf::Color(239, 68, 245));
        toBeColored.setOutlineColor(sf::Color(181, 69, 195));
        break;
    }
}

void tetrisGameManager::drawWell(sf::RenderWindow& window, Well toBeDrawn)
{
    sf::RectangleShape block;
    block.setSize(sf::Vector2f(BLOCK_SIZE_PIXELS - BORDER_THICKNESS_PIXELS * 2, BLOCK_SIZE_PIXELS - BORDER_THICKNESS_PIXELS * 2));
    block.setOutlineThickness(BORDER_THICKNESS_PIXELS);
    sf::Vector2f pixelPosition(TETRIS_BOARD_LEFT, TETRIS_BOARD_TOP);
    BlockColors wellBoard[BOARD_HEIGHT][BOARD_WIDTH];
    toBeDrawn.getBoard(wellBoard);

    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (wellBoard[y][x] != Empty)
            {
                block.setPosition(pixelPosition + sf::Vector2f(x * BLOCK_SIZE_PIXELS + BORDER_THICKNESS_PIXELS, y * BLOCK_SIZE_PIXELS + BORDER_THICKNESS_PIXELS));
                setSfmlColors(block, wellBoard[y][x]);
                window.draw(block);
            }
        }
    }
}

void tetrisGameManager::drawTetrimino(sf::RenderWindow& window, Tetrimino toBeDrawn)
{
    sf::RectangleShape block;
    setSfmlColors(block, toBeDrawn.getColor());
    block.setSize(sf::Vector2f(BLOCK_SIZE_PIXELS - BORDER_THICKNESS_PIXELS * 2, BLOCK_SIZE_PIXELS - BORDER_THICKNESS_PIXELS * 2));
    block.setOutlineThickness(BORDER_THICKNESS_PIXELS);
    tetriminoLocation position = toBeDrawn.getLocation();
    sf::Vector2f pixelPosition;
    int tetriminoGrid[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];
    toBeDrawn.getGrid(tetriminoGrid);

    // Sets the initial pixel location to be the top left of the Tetrimino grid.
    pixelPosition.x = TETRIS_BOARD_LEFT + position.col * BLOCK_SIZE_PIXELS;
    pixelPosition.y = TETRIS_BOARD_TOP + position.row * BLOCK_SIZE_PIXELS;

    for (int y = 0; y < TETRIMINO_GRID_SIZE; y++)
        for (int x = 0; x < TETRIMINO_GRID_SIZE; x++)
            if (tetriminoGrid[y][x] == 1)
            {
                block.setPosition(pixelPosition + sf::Vector2f(x * BLOCK_SIZE_PIXELS + BORDER_THICKNESS_PIXELS, y * BLOCK_SIZE_PIXELS + BORDER_THICKNESS_PIXELS));
                window.draw(block);
            }
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
        tetriminoInPlay = new Tetrimino(random_shape);
        tetriminoInPlay->setLocation(0, 4);
        tetriminoIsInPlay = true;
        autoDropTimer.restart();
    }

    manageButtonDelays(inputs.buttons);

    // Take actions based on input
    bool isStuck = false;
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

    drawTetrimino(window, *tetriminoInPlay);
    drawWell(window, gameBoard);
    if(isStuck)
    {
        delete tetriminoInPlay;
        tetriminoIsInPlay = false;
    }
}

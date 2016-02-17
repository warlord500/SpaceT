#include <tetris/TetrisManager.h>
#include <SFML/Graphics.hpp>
#include <tetris/Enums.h>

tetrisGameManager::tetrisGameManager(int windowHeight, int windowWidth) : WINDOW_HEIGHT(windowHeight), WINDOW_WIDTH(windowWidth)
{
    tetriminoIsInPlay = false;
}

bool  tetrisGameManager::checkLoseCondition()
{
    return gameBoard.topReached();
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
                switch(wellBoard[y][x])
                {
                case Cyan:
                    block.setFillColor(sf::Color::Cyan);
                    block.setOutlineColor(sf::Color(96, 216, 220));
                    break;
                case Yellow:
                    block.setFillColor(sf::Color::Yellow);
                    block.setOutlineColor(sf::Color(222, 222, 79));
                    break;
                case Orange:
                    block.setFillColor(sf::Color(255, 166, 31));
                    block.setOutlineColor(sf::Color(192, 124, 22));
                    break;
                case Blue:
                    block.setFillColor(sf::Color::Blue);
                    block.setOutlineColor(sf::Color(23, 19, 138));
                    break;
                case Green:
                    block.setFillColor(sf::Color::Green);
                    block.setOutlineColor(sf::Color(42, 183, 37));
                    break;
                case Red:
                    block.setFillColor(sf::Color::Red);
                    block.setOutlineColor(sf::Color(195, 25, 30));
                    break;
                case Purple:
                    block.setFillColor(sf::Color(239, 68, 245));
                    block.setOutlineColor(sf::Color(181, 69, 195));
                    break;
                }
                window.draw(block);
            }
        }
    }
}

void tetrisGameManager::drawTetrimino(sf::RenderWindow& window, Tetrimino toBeDrawn)
{
    sf::RectangleShape block;
    switch(toBeDrawn.getColor())
    {
    case Cyan:
        block.setFillColor(sf::Color::Cyan);
        block.setOutlineColor(sf::Color(96, 216, 220));
        break;
    case Yellow:
        block.setFillColor(sf::Color::Yellow);
        block.setOutlineColor(sf::Color(222, 222, 79));
        break;
    case Orange:
        block.setFillColor(sf::Color(255, 166, 31));
        block.setOutlineColor(sf::Color(192, 124, 22));
        break;
    case Blue:
        block.setFillColor(sf::Color::Blue);
        block.setOutlineColor(sf::Color(23, 19, 138));
        break;
    case Green:
        block.setFillColor(sf::Color::Green);
        block.setOutlineColor(sf::Color(42, 183, 37));
        break;
    case Red:
        block.setFillColor(sf::Color::Red);
        block.setOutlineColor(sf::Color(195, 25, 30));
        break;
    case Purple:
        block.setFillColor(sf::Color(239, 68, 245));
        block.setOutlineColor(sf::Color(181, 69, 195));
        break;
    }

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

void tetrisGameManager::playTetris(sf::RenderWindow& window, TetrisButtons buttons)
{
    if(!tetriminoIsInPlay)
    {
        tetriminoInPlay = new Tetrimino(L_shape);
        tetriminoInPlay->setLocation(0, 4);
        tetriminoIsInPlay = true;
    }

    if(buttons.quickDrop)
    {

    }
    else
    {
    	if(buttons.moveLeft)
		{

		}
        if(buttons.moveLeft)
        {

        }
        else if(buttons.moveRight)
        {

        }
        if(buttons.rotateRight)
        {

        }
        else if(buttons.rotateLeft)
        {

        }
    }


    drawTetrimino(window, *tetriminoInPlay);
    if(true) //condition for tetrimino has been put in well
    {
        delete tetriminoInPlay;
        tetriminoIsInPlay = false;
    }
}

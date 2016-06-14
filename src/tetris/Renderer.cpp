#include <tetris/Renderer.h>
#include <tetris/Well.h>
#include <tetris/Tetrimino.h>

using namespace Tetris;

Renderer::Renderer(int windowHeight, int windowWidth) : WINDOW_HEIGHT(windowHeight), WINDOW_WIDTH(windowWidth)
{
	block.setSize(sf::Vector2f(BLOCK_SIZE_PIXELS - BORDER_THICKNESS_PIXELS * 2, BLOCK_SIZE_PIXELS - BORDER_THICKNESS_PIXELS * 2));
    block.setOutlineThickness(BORDER_THICKNESS_PIXELS);

    nextPixelPosition.x = TETRIS_BOARD_LEFT + (BOARD_WIDTH + 1) * BLOCK_SIZE_PIXELS;
	nextPixelPosition.y = TETRIS_BOARD_TOP + -1 * BLOCK_SIZE_PIXELS;
	holdPixelPosition.x = nextPixelPosition.x;
	holdPixelPosition.y = 0;

    font.loadFromFile("assets/Fonts/tetricide.ttf");

    // Initialize texts text
    nextTetrimino.setFont(font);
    nextTetrimino.setString("NEXT");
    nextTetrimino.setCharacterSize(BLOCK_SIZE_PIXELS * 2);
    nextTetrimino.setPosition(TETRIS_BOARD_LEFT + BOARD_WIDTH * BLOCK_SIZE_PIXELS, TETRIS_BOARD_TOP + BLOCK_SIZE_PIXELS * 2);

    hold.setFont(font);
    hold.setString("HOLD");
    hold.setCharacterSize(BLOCK_SIZE_PIXELS * 2);
    hold.setPosition(TETRIS_BOARD_LEFT + BOARD_WIDTH * BLOCK_SIZE_PIXELS, TETRIS_BOARD_TOP + BLOCK_SIZE_PIXELS * 6);
}

void Renderer::setSfmlColors(sf::RectangleShape& toBeColored, const BlockColors color)
{
    switch(color)
    {
	case Staging:
		toBeColored.setFillColor(sf::Color(192, 192, 192));
		toBeColored.setOutlineColor(sf::Color(192, 192, 192));
		break;
	case Empty:
		toBeColored.setFillColor(sf::Color::White);
		toBeColored.setOutlineColor(sf::Color::White);
		break;
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

void Renderer::drawWell(sf::RenderWindow& window, const Well &toBeDrawn)
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
			block.setPosition(pixelPosition + sf::Vector2f(x * BLOCK_SIZE_PIXELS + BORDER_THICKNESS_PIXELS, y * BLOCK_SIZE_PIXELS + BORDER_THICKNESS_PIXELS));
			if(y < 2)
				setSfmlColors(block, Staging);
			else
				setSfmlColors(block, wellBoard[y][x]);
			window.draw(block);
        }
    }
}

void Renderer::drawTetrimino(sf::RenderWindow &window, const Tetrimino &toBeDrawn, const sf::Vector2f &pixelPosition)
{
    setSfmlColors(block, toBeDrawn.getColor());
    int tetriminoGrid[TETRIMINO_GRID_SIZE][TETRIMINO_GRID_SIZE];
    toBeDrawn.getGrid(tetriminoGrid);

	/*if(isNextPiece)
		// Sets the initial pixel location to on the top of and to the right of the Well.
		pixelPosition.x = TETRIS_BOARD_LEFT + (BOARD_WIDTH + 1) * BLOCK_SIZE_PIXELS;
	else
		// Sets the initial pixel location to be the top left of the Well.
		pixelPosition.x = TETRIS_BOARD_LEFT + position.col * BLOCK_SIZE_PIXELS;
	pixelPosition.y = TETRIS_BOARD_TOP + position.row * BLOCK_SIZE_PIXELS;
	*/
    for (int y = 0; y < TETRIMINO_GRID_SIZE; y++)
        for (int x = 0; x < TETRIMINO_GRID_SIZE; x++)
            if (tetriminoGrid[y][x] == 1)
            {
                block.setPosition(pixelPosition + sf::Vector2f(x * BLOCK_SIZE_PIXELS + BORDER_THICKNESS_PIXELS, y * BLOCK_SIZE_PIXELS + BORDER_THICKNESS_PIXELS));
                window.draw(block);
            }
}

void Renderer::drawInPlay(sf::RenderWindow &window, const Tetrimino &toBeDrawn)
{
	tetriminoLocation position = toBeDrawn.getLocation();
	sf::Vector2f pixelPosition = {TETRIS_BOARD_LEFT + position.col * BLOCK_SIZE_PIXELS, TETRIS_BOARD_TOP + position.row * BLOCK_SIZE_PIXELS};

    drawTetrimino(window, toBeDrawn, pixelPosition);
}

void Renderer::drawNext(sf::RenderWindow &window, const Tetrimino &toBeDrawn)
{
	drawTetrimino(window, toBeDrawn, nextPixelPosition);
}

void Renderer::drawHold(sf::RenderWindow &window, const Tetrimino &toBeDrawn)
{
	drawTetrimino(window, toBeDrawn, holdPixelPosition);
}

void Renderer::drawNextText(sf::RenderWindow &window)
{
	window.draw(nextTetrimino);
}

void Renderer::drawHoldText(sf::RenderWindow &window)
{
	window.draw(hold);
}

void Renderer::drawLevelUpText(sf::RenderWindow &window)
{
	window.draw(levelUp);
}

void Renderer::drawGameOverText(sf::RenderWindow &window)
{
	window.draw(gameOver);
}

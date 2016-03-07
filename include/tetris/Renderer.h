#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <tetris/Tetrimino.h>
#include <tetris/Well.h>

namespace Tetris
{
class Renderer
{
private:
	const int WINDOW_HEIGHT;
	const int WINDOW_WIDTH;
	const static int TETRIS_BOARD_TOP = 0;
	const static int TETRIS_BOARD_LEFT = 0;
	const static int BLOCK_SIZE_PIXELS = 20;
	const static int BORDER_THICKNESS_PIXELS = 2;

	void setSfmlColors(sf::RectangleShape& toBeColored, const BlockColors color);

public:
	Renderer(int windowHeight, int windowWidth);
	void drawWell(sf::RenderWindow& window, Well toBeDrawn);
    void drawTetrimino(sf::RenderWindow& window, Tetrimino toBeDrawn, bool isNextPiece = false);
};
}

#endif

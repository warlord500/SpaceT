#ifndef TETRIS_MANAGER_H
#define TETRIS_MANAGER_H

#include <SFML/Graphics.hpp>
#include <tetris/Enums.h>
#include <tetris/Tetrimino.h>
#include <tetris/Well.h>

struct TetrisButtons
{
	bool moveLeft;
	bool moveRight;
	bool rotateRight;
	bool rotateLeft;
	bool drop;
	bool quickDrop;
};

class tetrisGameManager
{
private:
    const int WINDOW_HEIGHT;
    const int WINDOW_WIDTH;
    const static int TETRIS_BOARD_TOP = 10;
    const static int TETRIS_BOARD_LEFT = 200;
    const static int BLOCK_SIZE_PIXELS = 36;
    const static int BORDER_THICKNESS_PIXELS = 5;

    Tetrimino* tetriminoInPlay;
    Well gameBoard;
    bool tetriminoIsInPlay;

    void drawWell(sf::RenderWindow& window, Well toBeDrawn) const;
    void drawTetrimino(sf::RenderWindow& window, Tetrimino toBeDrawn) const;
public:
    tetrisGameManager(int windowHeight, int windowWidth);
    void playTetris(sf::RenderWindow& window, TetrisButtons buttons);
};

#endif // TETRISGAMEMANAGER_H

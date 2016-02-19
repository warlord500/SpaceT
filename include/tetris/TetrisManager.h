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

struct TetrisInputs
{
    TetrisButtons buttons;
    // Add things here when we get around to
    // linking the two games together
};

struct TetrisOutputs
{

};

class tetrisGameManager
{
private:
    const int WINDOW_HEIGHT;
    const int WINDOW_WIDTH;
    const static int TETRIS_BOARD_TOP = 10;
    const static int TETRIS_BOARD_LEFT = 200;
    const static int BLOCK_SIZE_PIXELS = 20;
    const static int BORDER_THICKNESS_PIXELS = 2;
    const static int BUTTON_HOLD_DELAY = 250; // In milliseconds
    const static int AUTO_DROP_TIMER = 1000; // In milliseconds

    Tetrimino* tetriminoInPlay;
    Tetrimino* nextTetrimino;
    Well gameBoard;
    bool tetriminoIsInPlay;

	TetrisButtons wasPressed;
    sf::Clock moveLeftTimer;
    sf::Clock moveRightTimer;
    sf::Clock rotateRightTimer;
    sf::Clock rotateLeftTimer;
    sf::Clock dropTimer;
    sf::Clock quickDropTimer;
    sf::Clock autoDropTimer;

    TetrisOutputs tetrisOutputs;

    void setSfmlColors(sf::RectangleShape& toBeColored, const BlockColors color);
    void drawWell(sf::RenderWindow& window, Well toBeDrawn);
    void drawTetrimino(sf::RenderWindow& window, Tetrimino toBeDrawn);
    bool manageButtonDelay(sf::Clock& timer, const bool isPressed, bool& wasPressed);
    void manageButtonDelays(TetrisButtons& rawButtons);
public:
    tetrisGameManager(int windowHeight, int windowWidth);
    TetrisOutputs playTetris(sf::RenderWindow& window, TetrisInputs inputs);
};

#endif // TETRISGAMEMANAGER_H

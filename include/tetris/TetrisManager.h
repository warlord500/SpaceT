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
    const static int BLOCK_SIZE_PIXELS = 20;
    const static int BORDER_THICKNESS_PIXELS = 2;
    const static int BUTTON_HOLD_DELAY = 250; // In milliseconds
    const static int AUTO_DROP_TIMER = 1000; // In milliseconds

    Tetrimino* tetriminoInPlay;
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

    void drawWell(sf::RenderWindow& window, Well toBeDrawn) const;
    void drawTetrimino(sf::RenderWindow& window, Tetrimino toBeDrawn) const;
    bool manageButtonDelay(sf::Clock& timer, const bool isPressed, bool& wasPressed);
    void manageButtonDelays(TetrisButtons& rawButtons);
public:
    tetrisGameManager(int windowHeight, int windowWidth);
    void playTetris(sf::RenderWindow& window, TetrisButtons buttons);
};

#endif // TETRISGAMEMANAGER_H

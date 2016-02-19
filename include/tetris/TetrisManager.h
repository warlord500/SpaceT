#ifndef TETRIS_MANAGER_H
#define TETRIS_MANAGER_H

#include <SFML/Graphics.hpp>
#include <tetris/Renderer.h>
#include <tetris/Well.h>
#include <tetris/Tetrimino.h>
#include <tetris/Enums.h>

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

class tetrisGameManager : private Renderer
{
private:
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

    bool manageButtonDelay(sf::Clock& timer, const bool isPressed, bool& wasPressed);
    void manageButtonDelays(TetrisButtons& rawButtons);
public:
    tetrisGameManager(int windowHeight, int windowWidth);
    TetrisOutputs playTetris(sf::RenderWindow& window, TetrisInputs inputs);
};

#endif // TETRISGAMEMANAGER_H

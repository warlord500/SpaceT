#ifndef TETRIS_MANAGER_H
#define TETRIS_MANAGER_H

#include <SFML/Graphics.hpp>
#include <tetris/Renderer.h>
#include <tetris/Well.h>
#include <tetris/Tetrimino.h>
#include <tetris/Text.h>
#include <tetris/Enums.h>

namespace Tetris
{
struct Buttons
{
    bool moveLeft;
    bool moveRight;
    bool rotateRight;
    bool rotateLeft;
    bool drop;
    bool quickDrop;
};

struct Inputs
{
    Buttons buttons;
    // Add things here when we get around to
    // linking the two games together
};

struct Outputs
{
    bool gameOver;
};

class GameManager
{
private:
    // Tetris settings
    const static int BUTTON_HOLD_DELAY = 250; // In milliseconds
    const static int INITIAL_DROP_TIME = 250;//1000; // In milliseconds

    // Game control
    Tetrimino* tetriminoInPlay;
    Tetrimino* nextTetrimino;
    Well gameBoard;
    Renderer renderer;
    Text text;
    Outputs outputs;
    bool tetriminoIsInPlay;
    bool isStuck;
    int dropTime;

    // Button management
    Buttons wasPressed;
    sf::Clock moveLeftTimer;
    sf::Clock moveRightTimer;
    sf::Clock rotateRightTimer;
    sf::Clock rotateLeftTimer;
    sf::Clock dropTimer;
    sf::Clock quickDropTimer;
    sf::Clock autoDropTimer;

    bool manageButtonDelay(sf::Clock& timer, const bool isPressed, bool& wasPressed);
    void manageButtonDelays(Buttons& rawButtons);
public:
    GameManager(int windowHeight, int windowWidth);
    ~GameManager();
    Outputs play(sf::RenderWindow& window, Inputs inputs);
};
}

#endif // TETRISGAMEMANAGER_H

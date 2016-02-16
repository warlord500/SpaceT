#ifndef TETRISGAMEMANAGER_H
#define TETRISGAMEMANAGER_H
#include <tetris/tetrisEnums.h>
#include <tetris/tetrisMovableShape.h>
#include "main.h"
#include <SFML/System/Vector2.hpp>
namespace sf
{
class RenderWindow;
}

/*
    Class: tetrisGameManager

        this classes handless
    everything to deal with tetris game side
    currently being worked on.

    cyclic refernces:
        tetrisMovable - current used as owner.

    Depends on:
        <tetrisMovable>

*/
class tetrisGameManager
{
    //friend class tetrisMovableShape;
private:
    const static int blockGridSize_Y = 24;
    const static int blockGridSize_X = 10;
    const static int borderThickness = 5;

    int blockGrid[blockGridSize_X][blockGridSize_Y];
    bool gameOver; // needs to a way to signal game over condition met
    tetrisMovableShape playingShape;
    void drawGrid(sf::RenderWindow& window);
    void checkLines();
    bool checkLoseCondition();
public:
    tetrisGameManager();
    void updateGrid(sf::RenderWindow& window);
    //const sf::Vector2f(blockGridSize_X * screenHeight blockGridSize_Y, screenHeight);
};

#endif // TETRISGAMEMANAGER_H

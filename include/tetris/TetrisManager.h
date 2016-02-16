#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include <tetris/Enums.h>
#include <tetris/MovableShape.h>

class tetrisGameManager
{
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
};

#endif // TETRISGAMEMANAGER_H

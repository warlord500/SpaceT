#ifndef TETRIS_MANAGER_H
#define TETRIS_MANAGER_H

#include <SFML/Graphics.hpp>
#include <tetris/Enums.h>
#include <tetris/Tetrimino.h>

class tetrisGameManager
{
private:
    const int WINDOW_HEIGHT;
    const int WINDOW_WIDTH;
    const static int TETRIS_BOARD_TOP = 10;
    const static int TETRIS_BOARD_LEFT = 200;
    const static int BLOCK_SIZE_PIXELS = 20;
    const static int BORDER_THICKNESS_PIXELS = 5;

    Tetrimino tetriminoInPlay;
    void drawWell(sf::RenderWindow& window);
    void drawTetrimino(sf::RenderWindow& window);
    void checkLines();
    bool checkLoseCondition();
public:
    tetrisGameManager(int windowHeight, int windowWidth);
    void updateGrid(sf::RenderWindow& window);
};

#endif // TETRISGAMEMANAGER_H

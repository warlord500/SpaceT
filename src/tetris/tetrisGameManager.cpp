#include <tetris/tetrisGameManager.h>
#include  <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "main.h"
#include <tetris/tetrisEnums.h>
/**
    this file is in major need of reformatting
    it has broken two major guidelines
    the 200 lines per file rule
    and the 4 indentations limit.
    and the code need to be re formatted
*/
/// setup a tetris game.
tetrisGameManager::tetrisGameManager() : gameOver(false), playingShape(*this)
{
    ///reset the entire block grid to none
    for(int x = 0; x < tetrisGameManager::blockGridSize_X; x++)
    {
        for(int y = 0; y < tetrisGameManager::blockGridSize_Y; y++)
        {
            blockGrid[x][y] = Empty;
        }
    }

    /// create a inital start piece
    this->playingShape.createBlock(Red);
}
void tetrisGameManager::checkLines()
{

    int blocks = 0; /// number of blocks in a line that arent empty
    bool lines[blockGridSize_Y]; /// represent each line
    int times = 0;
    /// make sure that all of the lines are false
    /// please avoid using numeric constants
    for(int y = 0; y < blockGridSize_Y; y++)
        lines[y] = false;
    for(int y = 0; y < blockGridSize_Y; y++)
    {
        for(int x = 0; x < blockGridSize_X; x++)
        {
            if(blockGrid[x][y] != Empty)
                blocks++;
        }
        if(blocks == blockGridSize_X) /// all blocks are filled
            lines[y] = true;
        blocks = 0;
    }
    for(int y = (blockGridSize_Y - 1); y  > 0; y--)
    {
        if(lines[y])
            times++;
        /// shift blocks down to their new correct positon
        for(int x = 0; x < blockGridSize_X; x++)
            blockGrid[x][y] = blockGrid[x][y - times];
    }
}
bool  tetrisGameManager::checkLoseCondition()
{
        if(blockGrid[4][0] != Empty || blockGrid[5][0] != Empty ||
            blockGrid[6][0] != Empty || blockGrid[7][0] != Empty)
        return false;
    return true;
}

void tetrisGameManager::drawGrid(sf::RenderWindow& window)
{   //first calculate the size of single side of a block with padding
    const int blockSizeFull = screenHeight/blockGridSize_Y;
    // remove the padding. there are two side which are padded remove both.
    const int BlockSizeReal = blockSizeFull -(borderThickness*2);

    sf::RectangleShape block(sf::Vector2f(BlockSizeReal, BlockSizeReal));
    block.setOutlineThickness(borderThickness);
    for(int x = 0; x < blockGridSize_X; x++)
    {
        for(int y = 0; y < blockGridSize_Y; y++)
        {
            // apply the padding offset and then calculate the distance of block form screen.
            block.setPosition((x * blockSizeFull) + borderThickness,
                                    y * (blockSizeFull) + borderThickness);
            switch(blockGrid[x][y])
            {
            case Empty:
                block.setFillColor(sf::Color::Black);
                block.setOutlineColor(sf::Color::Black);
                break;
            case Cyan:
                block.setFillColor(sf::Color::Cyan);
                block.setOutlineColor(sf::Color(96, 216, 220, 225));
                break;
            case Yellow:
                block.setFillColor(sf::Color::Yellow);
                block.setOutlineColor(sf::Color(222, 222, 79, 225));
                break;
            case Orange:
                block.setFillColor(sf::Color(255, 166, 31, 255));
                block.setOutlineColor(sf::Color(192, 124, 22, 255));
                break;
            case Blue:
                block.setFillColor(sf::Color::Blue);
                block.setOutlineColor(sf::Color(23, 19, 138, 255));
                break;
            case Green:
                block.setFillColor(sf::Color::Green);
                block.setOutlineColor(sf::Color(42, 183, 37, 255));
                break;
            case Red:
                block.setFillColor(sf::Color::Red);
                block.setOutlineColor(sf::Color(195, 25, 30, 255));
                break;
            case Purple:
                block.setFillColor(sf::Color(239, 68, 245, 255));
                block.setOutlineColor(sf::Color(181, 69, 195, 255));
                break;
            }
            window.draw(block);
        }
    }
}

void tetrisGameManager::updateGrid(sf::RenderWindow& window)
{

    this->playingShape.move();
    this->checkLines();
    if(this->checkLoseCondition())
        this->gameOver = true; // game over signal needs to be invoked.
    this->drawGrid(window);
}

#include <tetris/TetrisManager.h>
#include  <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "main.h"
#include <tetris/Enums.h>

tetrisGameManager::tetrisGameManager()
{

}

void tetrisGameManager::checkLines()
{


}

bool  tetrisGameManager::checkLoseCondition()
{

    return false;
}

void tetrisGameManager::drawGrid(sf::RenderWindow& window)
{
    // This could be useful.
    /*switch(blockGrid[x][y])
    {
    case Empty:
        block.setFillColor(sf::Color::Black);
        block.setOutlineColor(sf::Color::Black);
        break;
    case Cyan:
        block.setFillColor(sf::Color::Cyan);
        block.setOutlineColor(sf::Color(96, 216, 220, 255));
        break;
    case Yellow:
        block.setFillColor(sf::Color::Yellow);
        block.setOutlineColor(sf::Color(222, 222, 79, 255));
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
    }*/
}

void tetrisGameManager::updateGrid(sf::RenderWindow& window)
{


}

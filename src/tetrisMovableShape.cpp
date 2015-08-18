#include "tetrisMovableShape.h"
#include <SFML/Window/Keyboard.hpp>
#include <chrono>
#include <tetrisGameManager.h>
#include <random>
tetrisMovableShape::tetrisMovableShape(tetrisGameManager& gm) : horizontalCooldown(false) , verticalCooldown(false),
    end_time(std::chrono::system_clock::now() + std::chrono::milliseconds(250)), gameManager(gm)
{
}

void tetrisMovableShape::createRandomNormBlock()
{
    switch(rand() % 7 + 1)
    {
    case 1:
        createBlock(Cyan);
        break;
    case 2:
        createBlock(Yellow);
        break;
    case 3:
        createBlock(Orange);
        break;
    case 4:
        createBlock(Blue);
        break;
    case 5:
        createBlock(Green);
        break;
    case 6:
        createBlock(Red);
        break;
    case 7:
        createBlock(Purple);
        break;
    };
}

/// creates a block piece -- recommend moving to tetris block class.
void tetrisMovableShape::createBlock(BlockColors status)
{
    /// note what shape describing with what color
    switch(status)
    {
    case Cyan:
        for(int x = 0; x < 4; x++)
        {
            movingx[x] = x + 3;
            movingy[x] = 0;
        }
        break;
    case Yellow:
        for(int x = 0; x < 4; x++)
        {
            if(x < 3)
            {
                movingx[x] = x + 3;
                movingy[x] = 1;
            }
            else
            {
                movingx[x] = 5;
                movingy[x] = 0;
            }
        }
        break;
    case Orange:
        for(int x = 0; x < 4; x++)
        {
            if(x < 3)
            {
                movingx[x] = x + 3;
                movingy[x] = 0;
            }
            else
            {
                movingx[x] = 5;
                movingy[x] = 1;
            }
        }
        break;
    case Blue:
        for(int x = 0; x < 4; x++)
        {
            if(x < 2)
            {
                movingx[x] = x + 4;
                movingy[x] = 0;
            }
            else
            {
                movingx[x] = x + 2;
                movingy[x] = 1;
            }
        }
        break;
    case Green:
        for(int x = 0; x < 4; x++)
        {
            if(x < 2)
            {
                movingx[x] = x + 3;
                movingy[x] = 1;
            }
            else
            {
                movingx[x] = x + 2;
                movingy[x] = 0;
            }
        }
        break;
    case Red:
        for(int x = 0; x < 4; x++)
        {
            if(x < 2)
            {
                movingx[x] = x + 3;
                movingy[x] = 0;
            }
            else
            {
                movingx[x] = x + 2;
                movingy[x] = 1;
            }
        }
        break;
    case Purple:
        for(int x = 0; x < 4; x++)
        {
            if(x != 3)
            {
                movingx[x] = x + 3;
                movingy[x] = 1;
            }
            else
            {
                movingx[x] = x + 1;
                movingy[x] = 0;
            }
        }
        break;
    default:
        break;
    }
    /// what is happening here why am i doing this?
    currentBlock = status;
}

/// which blocks am i moving
/// why am i returning a booleans
void tetrisMovableShape::move(void)
{


    if(!horizontalCooldown)
    {
        bool safeRight = true;
        bool safeLeft = true;
        for(unsigned int i = 0; i < movingx.size(); i++)
        {
            bool LeftSafeBefore = false;
            bool RightSafeBefore = false;
            LeftSafeBefore  |= (gameManager.blockGrid[movingx[i]-1][movingy[i]] == Empty);
            RightSafeBefore |= (gameManager.blockGrid[movingx[i]+1][movingy[i]] == Empty);
            for(unsigned int k = 0; k < movingx.size(); k++)
            {
                LeftSafeBefore|= ( (movingx[i]-1 == movingx[k]) && movingy[i] == movingy[k]);
                RightSafeBefore |= ( (movingx[i]+1 == movingx[k]) && movingy[i] == movingy[k]);
            }
            safeLeft &= !(movingx[i]-1 == -1);
            safeLeft &= LeftSafeBefore;
            safeRight &= RightSafeBefore;
            safeRight &= !(movingx[i]+1 == tetrisGameManager::blockGridSize_X - 1);

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& safeLeft)
        {
            /*
                check if the closest block to the side of the wall is
                going to go off screen.
            */
            horizontalCooldown = true;
            for(int x = 0; x < 4; x++)
            {
                gameManager.blockGrid[movingx[x]][movingy[x]] = Empty;
                movingx[x] = movingx[x] - 1;
                gameManager.blockGrid[movingx[x]][movingy[x]] = this->currentBlock;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) & safeRight)
        {
            horizontalCooldown = true;
            for(int x = 0; x < 4; x++)
            {
                gameManager.blockGrid[movingx[x]][movingy[x]] = Empty;
                movingx[x] = movingx[x] + 1;
                gameManager.blockGrid[movingx[x]][movingy[x]] = this->currentBlock;
            }
        }
    }
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        horizontalCooldown = false;
        for(int x = 0; x < 4; x++)
        {
            gameManager.blockGrid[movingx[x]][movingy[x]] = this->currentBlock;
        }
    }

    /// this is really bad formatted code that looks extremely hard to adjust
    /// this really needs to broken up to different if statements
    /// looping through array would be more flexible and eaiser to read

    ///vertical movement checking implemented here
    if(end_time < std::chrono::system_clock::now() || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !verticalCooldown)
    {
        /// please rewrite using a for loop system
        if((gameManager.blockGrid[movingx[0]][movingy[0]+1] == Empty || (movingy[0] + 1 == movingy[1] && movingx[0] == movingx[1]) ||
                (movingy[0] + 1 == movingy[2] && movingx[0] == movingx[2]) ||
                (movingy[0] + 1 == movingy[3] && movingx[0] == movingx[3]))
                &&(gameManager.blockGrid[movingx[1]][movingy[1]+1] == Empty || (movingy[1] + 1 == movingy[0] && movingx[1] == movingx[0]) ||
                   (movingy[1] + 1 == movingy[2] && movingx[1] == movingx[2]) ||
                   (movingy[1] + 1 == movingy[3] && movingx[1] == movingx[3]))
                &&(gameManager.blockGrid[movingx[2]][movingy[2]+1] == Empty || (movingy[2] + 1 == movingy[0] && movingx[2] == movingx[0]) ||
                   (movingy[2] + 1 == movingy[1] && movingx[2] == movingx[1]) ||
                   (movingy[2] + 1 == movingy[3] && movingx[2] == movingx[3]))
                &&(gameManager.blockGrid[movingx[3]][movingy[3]+1] == Empty || (movingy[3] + 1 == movingy[0] && movingx[3] == movingx[0]) ||
                   (movingy[3] + 1 == movingy[1] && movingx[3] == movingx[1]) ||
                   (movingy[3] + 1 == movingy[2] && movingx[3] == movingx[2]))
                && movingy[0] < 23 && movingy[1] < 23 && movingy[2] < 23 && movingy[3] < 23)
        {
            /// what does this loop do?
            /// how does it work?
            for(int x = 0; x < 4; x++)
            {
                gameManager.blockGrid[movingx[x]][movingy[x]] = Empty;
                movingy[x] = movingy[x] + 1;
                gameManager.blockGrid[movingx[x]][movingy[x]] = this->currentBlock;
            }
            verticalCooldown = true;
        }
        else
        {
            this->createRandomNormBlock();
        }
        end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(250);
    }
    else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        verticalCooldown = false;
}

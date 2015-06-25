#include "space_invaders/spaceInvManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "main.h"
#include <space_invaders/textureManager.h>
const static float moveSpeed = 4.0f;

spaceInvManager::spaceInvManager(const textureManager& images,const sf::FloatRect& screenRect) :
        //initilize the player with texture and screenRect
    thePlayer(3,images.getTexture("player.png"),
            sf::Vector2f(screenRect.left,(screenRect.height + screenRect.top)- player::sizeOfPLayerSides)) ,
    images(images)
{
    //create a starting enemy
    enemy NewEnemy(this->images.getTexture("enemy.png"),sf::Vector2f(screenRect.left+50.0f,0.0f));
    this->enemiesList.push_back(NewEnemy);
}
void spaceInvManager::KeyEvents(const sf::FloatRect& screenSize)
{
    // test if it is ok to shoot.
        if(thePlayer.shootBullet())
    {
        pBullet Nbullet(images.getTexture("bullet.png"),
                        thePlayer.getSprite().getPosition());
        this->playerBullets.push_back(Nbullet);

    }

     this->thePlayer.keyMovement(screenSize);
}

void spaceInvManager::update(sf::RenderWindow& app,const sf::FloatRect& screenSize)
{

     app.draw(thePlayer.getSprite());
    /*
        it is an iterator that points
        the current instance of the
        playerBullets.
    */
    auto it = playerBullets.begin();
    while( it != playerBullets.end())
    {
        if(it->calcSide(screenSize))
        {
            //get rid of bullets on the outside of the screen
            playerBullets.erase(it++);
        }
        else
        {
            it->logic();
            app.draw(it->getSprite());
            ++it;
        }
    }
    //note for next time
    //dont put semi colon before braces
    auto eneIT = this->enemiesList.begin();
    while( eneIT != this->enemiesList.end())
    {
        eneIT->logic();
        app.draw(eneIT->getSprite());
        auto it = playerBullets.begin();
        while((it != playerBullets.end()))
        {
            if((*it).intersects(eneIT->getSprite().getGlobalBounds()))
            {
                    enemiesList.erase(eneIT++);
                    playerBullets.erase(it++);
                    break;
            }
            ++it;
        };
        ++eneIT;
    }
    this->KeyEvents(screenSize);
}

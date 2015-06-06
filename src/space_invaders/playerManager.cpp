#include "space_invaders/playerManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "main.h"
#include <space_invaders/textureManager.h>
const static float moveSpeed = 4.0f;
playerManager::playerManager(const textureManager& images,sf::FloatRect screenComp) :
    thePlayer(3,images.getTexture("player.png"),
            sf::Vector2f(screenComp.left,(screenComp.height + screenComp.top)- player::sizeOfPLayerSides)) ,
    images(images) ,
    screenComp(screenComp)
{

}
void playerManager::drawItems(sf::RenderWindow& app)
{

    app.draw(thePlayer.getSprite());
    auto it = playerBullets.begin();
    while( it != playerBullets.end() )
    {
        app.draw(it->getSprite());
        ++it;
    }

}
void playerManager::checkSides()
{
    /*
        it is an iterator that points
        the current instance of the
        playerBullets.
    */
    auto it = playerBullets.begin();
    while( it != playerBullets.end() )
    {
        if(it->calcSide(screenComp))
        {
            //get rid of bullets on the outside of the screen
            playerBullets.erase(it++);
        }
        else
        {
            it->logic();
            ++it;
        }
    }
}
void playerManager::KeyEvents(void)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->lastShotTime < std::chrono::system_clock::now())
    {
        pBullet Nbullet(images.getTexture("bullet.png"),
                        thePlayer.getSprite().getPosition());
        playerBullets.push_back(Nbullet);
         this->lastShotTime = std::chrono::system_clock::now() + std::chrono::milliseconds(500);
    }

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        thePlayer.move(moveSpeed);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        // dont draw outside screen Rect.
        if(thePlayer.getSprite().getPosition(). x - moveSpeed > screenComp.left)
        thePlayer.move(-1.0f*moveSpeed); // go left
    }
}


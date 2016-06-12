#include "space_invaders/player.h"

using namespace SpaceInvaders;

const static float moveSpeed = 4.0f;
player::player(int lives,const sf::Texture& texture,const sf::Vector2f& pos) : sprite(texture),
    lives(lives)
{
    this->sprite.setPosition(pos);
}
bool player::shootBullet(void)
{
   //shoot only if the delay on shooter has passed
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->lastShotTime < std::chrono::system_clock::now())
    {
        this->lastShotTime = std::chrono::system_clock::now() + std::chrono::milliseconds(500);
        return true;
    }
    return false;
}

void player::keyMovement(const sf::FloatRect& screenRect)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->move(moveSpeed);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        // dont draw outside screen Rect.
        if(this->getSprite().getPosition(). x - moveSpeed > screenRect.left)
        this->move(-1.0f*moveSpeed); // go left instead of the normal right motion
    }
}


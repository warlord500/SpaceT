#include "space_invaders/bullet.h"

using namespace SpaceInvaders;

bullet::bullet(const sf::Texture& texture,const sf::Vector2f& pos) :  sprite(texture)
{
    this->sprite.setPosition(pos);
}

bullet::~bullet()
{
}

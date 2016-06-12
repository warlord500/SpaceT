#include "space_invaders/bullets/pBullet.hpp"

using namespace SpaceInvaders;

pBullet::pBullet(const sf::Texture& texture,const sf::Vector2f& pos) : bullet(texture,pos)
{
    //ctor
}

pBullet::~pBullet()
{
    //dtor
}

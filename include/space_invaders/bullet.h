#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H

#include <SFML/Graphics/Sprite.hpp>

/*
    Class: bullet
        generic bullet class
        not useful for player or enemy
    note:
        this class is 90% header only.

    todo:
        merge any all properties
        of this class with pbullet.

    Depends on:
        sf::sprite

    inherited by:
        <pBullet>
*/
namespace SpaceInvaders
{
class bullet
{
public:
    //Group: public

    /*
        Constructor: bullet(const sf::texture&,const sf::Vector2f&)
            build visual entity

        Parameters:
            texture - the texture the bullet is going to use
            pos - where to draw the bullet
    */
    bullet(const sf::Texture&, const sf::Vector2f& pos);

    // Function: getSprite
    inline const sf::Sprite& getSprite()
    {
        return this->sprite;
    }
    virtual ~bullet();
protected:
    // Group: protected

    //Function: move(float)
    // moves bullet in the y direction
     inline void move(float y)
    {
        this->sprite.move(sf::Vector2f(0,y));
    }

private:
     sf::Sprite sprite;
};
}

#endif // SPACEINVADERS_BULLET_H

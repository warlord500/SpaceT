#ifndef PLAYER_H
#define PLAYER_H
#include <chrono>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <chrono>
// TODO (jadon#1#): moves only long the x axis ...
//create function to do that
/*
    Class: player
        the player class for space invaders

    See Also:
        <playerManager> - manage players
*/
class player
{
public:
    /*
        Constructor: player(int,const sf::Texture&,const sf::Vector2f&)
            construct a player at the specifed spot and lives

        Parameters:
            lives(1) - the number of lives to initilize with
            images(2) - texture manager
            pos(3) - position to place player
    */
    player(int lives,const sf::Texture&,const sf::Vector2f& pos);
    /*
        function:keyMovement
            this functions reacts
            to when keys are being

        Parameters:
            screenSize(1) represents the screenrect
            the player may not draw it self out of.
    */

    void keyMovement(const sf::FloatRect& screenSize);
    /*
        Function: shotBullet
            test if player will shoot bullet.

        Return:
            willShoot
            true: ok to shoot bullet
            false: don't shoot bullet.
    */
    bool shootBullet(void);

    // Function: getLives()
    // get the lives of player
    inline unsigned int Getlives()
    {
        return lives;
    }
    // Function: hit()
    // destroy one life
   inline void hit()
    {
        lives -= 1;
    }

    // Function: getSprite()
    // get the sprite
    inline const sf::Sprite& getSprite()
    {
        return this->sprite;
    }
    //group: public static vars
    /*
        variable: sizeOfPlayersides

            varible is the length of player image
            in pixels for both x and y side..
    */
    // Function: move(float)
    // move the player across along the x axis
    inline void move(float x)
    {
        this->sprite.move(sf::Vector2f(x,0));
    }
     constexpr static float sizeOfPLayerSides = 50.0f;
protected:
private:
    //group: private
     sf::Sprite sprite; //!< Member variable "boundingRect"
    unsigned int lives; //!< Member variable "lives"
    std::chrono::time_point<std::chrono::system_clock> lastShotTime;
};

#endif // PLAYER_H

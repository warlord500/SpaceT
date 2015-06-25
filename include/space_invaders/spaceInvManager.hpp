#ifndef PLAYERMANGER_H
#define PLAYERMANGER_H
#include <space_invaders/player.h>
#include <space_invaders/bullets/pBullet.hpp>
#include <space_invaders/enemy.hpp>
#include <list>
#include <chrono>
class textureManager;
namespace sf
{
class RenderWindow;
}
/*
    Class: spaceInvadersManager
       manages and updates all entites on similar

    note:
        player ship is placed at the bottom of the screen.

    See Also:
        <player> - instance this class manages
        <pbullet> - player bullet
*/
class spaceInvManager
{
public:
    //group: public constructors
    /*
        Constructor: playerManager(const textureManage& images)
            construct playerManager using image DataBase.

        Parameters:
            images(1)  the image manager to be used
                by the playerManager.
            screenSize(2) set player base positon
                 with this screen size.


        Warning:
            images must live as long as their is
                playerManager is referring to it.

        See Also:
            <textureManager>
    */
    spaceInvManager(const textureManager& images,const sf::FloatRect&);
    //group: public methods
    /*
        function: update

        updates all instances involving the player on the space
        invaders game. this function handles
    */
    void update(sf::RenderWindow&,const sf::FloatRect&);




protected:
private:
// group: private data
     /*
        Function: drawItems(sf::RenderWindow&)
            draw the player and player bullets on window

        Parameters:
            app(1) -- the window to draw the player
                and the playerBullets on.
    */
    void drawItems(sf::RenderWindow& app);
    /*
        Function: checkSides(sf::FloatRect&)
            check if any of the player bullets
            have reached the end of the screen.
    */
    void checkSides(const sf::FloatRect&);
    /*
        Function: keyEvents
            checks events and the key board.

            this function checks the keyboard to
            see if the keys have been pressed.
    */
    void KeyEvents(const sf::FloatRect&);

    player thePlayer;
    const textureManager& images;
    std::list<pBullet> playerBullets;
    std::list<enemy> enemiesList;

};

#endif // PLAYERMANGER_H

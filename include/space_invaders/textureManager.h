#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>
/*

    Class: textureManager
        automanage the amount of textures loaded.

    simple texture manager keeps a map (key to value pairs)
    to of string and associatedloaded in memory.
    makes access to the map simpler and well designed for
    the intent of accessing the texture

    warning:
        this class is completely header only.

    Todo:
        add auto memory management
        change from map to unordered map

    Depends on:
        sf::texture
        std::map
        std::string
*/
class textureManager
{
public:
    // group: public

    /* Function: getTexture(std::string)
        get texture by id.
        the id is usally the name of the file.
    */
    inline const sf::Texture& getTexture(std::string key) const
    {
        return gameTextures.find(key)->second;
    }
    /*
        Function: getTexture(const char*)
        the overloaded version of the
        getTexture. allows programmer to not have to write extra
        characters later.

        Returns:
            refernce to the texture.

        See Also:
            <getTexture(std::string)>
    */
   inline const sf::Texture& getTexture(const char * key) const
    {
        /// note dont try to reuse above function. it ends calling
        /// this method causing infinte recurstivity
        std::string strKey(key);
        return  gameTextures.find(key)->second;
    }
    /*
        Function: addTexture(std::string,sf::Texture)
            adds textures using an id to refer later.

        See Also:
            <addTexture(const char*,sf::Texture)>
    */
    inline void addTexture(std::string& key,sf::Texture& texture)
    {
        gameTextures.insert(std::pair<std::string,sf::Texture>(key,texture));
    }
    /*
        Function: addTexture(const char*,sf::Texture)
            overloaded add texture

        See Also:
            <addTexture(std::string,sf:Texture)>
    */
    inline void addTexture(const char* key,sf::Texture& texture)
    {
        std::string strKey(key);
        this->addTexture(strKey,texture);
    }
    /*
        Function: addAllCommonTextures
            adds the most used texture in one spot

            this code adds all of textures that
            are used between the space invaders and
            tetris side of the projects.

        Returns:
            did we successfully compelete the proccess.
            true: - we completed successful
            false: we failed
    */
   inline bool addAllCommonTextures(void)
    {
        sf::Texture playerTexture;
        if (!playerTexture.loadFromFile("assets/player.png"))
            return false;
        this->addTexture("player.png",playerTexture);
        /*//player bullets
        sf::Texture pBulletTexture;
        if(!pBulletTexture.loadFromFile("assets/bullet.png"))
            return false;
        this->addTexture("assets/bullet.png",pBulletTexture);

        sf::Texture enemiesTexture;
        if(!enemiesTexture.loadFromFile("assets/enemy.png"))
            return false;
        this->addTexture("assets/enemy.png",enemiesTexture);
        */
        return true;
    }
protected:
private:
    std::map<std::string,sf::Texture> gameTextures;
};

#endif // TEXTUREMANAGER_H

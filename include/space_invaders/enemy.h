#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include <SFML/Graphics/Sprite.hpp>

/*
	Class: enemy
		enemy in space invaders game

	See Also:
		<enemyManager>
*/
namespace SpaceInvaders
{
class enemy
{
public:
	// Group: Constructors
	enemy(const sf::Texture& texture, const sf::Vector2f& pos);
	// Group: Public

	/*
		Function: logic
			updates the enemy states
	*/
	void logic(void);

	// Function: getSprite
	inline const sf::Sprite& getSprite()
	{
		return this->sprite;
	}
protected:
private:
	enum class dir
	{
		Left = 0,
		Right = 1
	};
	sf::Sprite sprite;
	const sf::Vector2f initPos;
	dir dirGoing;
};
}

#endif // SPACEINVADERS_ENEMY_H

#ifndef TEXT_H
#define TEXT_H

#include <SFML/Graphics.hpp>

namespace Tetris
{
class Text
{
private:
	sf::Font font;
	sf::Text nextTetrimino;
	sf::Text levelUp;
	sf::Text gameOver;
public:
	Text();
	void drawNext(sf::RenderWindow& window);
	void drawLevelUp(sf::RenderWindow& window);
	void drawGameOver(sf::RenderWindow& window);
};
}

#endif

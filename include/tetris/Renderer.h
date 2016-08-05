#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <tetris/Tetrimino.h>
#include <tetris/Well.h>

namespace Tetris
{
class Renderer
{
private:
    const sf::FloatRect SCREEN_RECT;
	const float BLOCK_SIZE_PIXELS; // 13*24 is the entire Tetris area in blocks
	const float BORDER_THICKNESS_PIXELS;

	sf::Font font;
	sf::Text nextTetrimino;
	sf::Text hold;
	sf::Text levelUp;
	sf::Text gameOver;

	sf::RectangleShape block;
	sf::Vector2f nextPixelPosition;
	sf::Vector2f holdPixelPosition;

	void setSfmlColors(sf::RectangleShape &toBeColored, const BlockColors color);
	void drawTetrimino(sf::RenderWindow &window, const Tetrimino &toBeDrawn, const sf::Vector2f &pixelPosition);
public:
	Renderer(const sf::FloatRect &screenRect);
	void drawWell(sf::RenderWindow &window, const Well &toBeDrawn);
    void drawInPlay(sf::RenderWindow &window, const Tetrimino &toBeDrawn);
    void drawNext(sf::RenderWindow &window, const Tetrimino &toBeDrawn);
    void drawHold(sf::RenderWindow &window, const Tetrimino &toBeDrawn);
    void drawNextText(sf::RenderWindow &window);
    void drawHoldText(sf::RenderWindow &window);
    void drawLevelUpText(sf::RenderWindow &window);
    void drawGameOverText(sf::RenderWindow &window);
};
}

#endif

#pragma once
#include <SFML/Graphics.hpp>
class Board
{
public:
	Board();
	void draw(sf::RenderWindow& window);

private:
	sf::Vector2f bigRectSize;
	sf::Color bigRectColor;
	sf::Vector2f smallRectSize;
	sf::Color rectColor;
	sf::RectangleShape bigRectangles[9];
	sf::RectangleShape smallRectangles[9][9];
	float gap;
	float smallGap;
};

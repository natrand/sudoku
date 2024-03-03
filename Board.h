#pragma once
#include <SFML/Graphics.hpp>
class Board
{
public:
	Board();
	void draw(sf::RenderWindow& window);
	void GenerateRandomNumbers();
	void updateNumbers(const std::vector<std::vector<int>>& SudokuBoard, sf::RenderWindow& window);
	const std::vector<std::vector<int>>& getSudokuBoard() const { return SudokuBoard; }
private:
	sf::Vector2f bigRectSize;
	sf::Color bigRectColor;
	sf::Vector2f smallRectSize;
	sf::Color rectColor;
	sf::RectangleShape bigRectangles[9];
	sf::RectangleShape smallRectangles[9][9];
	float gap;
	float smallGap;
	std::vector<std::vector<int>> SudokuBoard;
	static constexpr int textSize = 24;
	sf::Font font;


};


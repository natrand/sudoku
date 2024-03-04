#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Board
{
public:
	Board();
	void draw(sf::RenderWindow& window);
	void GenerateRandomNumbers();
	void updateNumbers(const std::vector<std::vector<int>>& SudokuBoard, sf::RenderWindow& window);
	const std::vector<std::vector<int>>& getSudokuBoard() const { return SudokuBoard; }
	bool isSafe() const;
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
	bool generateSudokuBoard(int row, int col);
	bool isValidMove(int row, int col, int num) const;

};


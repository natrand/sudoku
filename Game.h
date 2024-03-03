#pragma once

#include "Board.h"

class Game
{
public:
	Game();

	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void StartGame();
	Board& getBoard();
	void startTimer();
	void setTimerText(const std::string& text);

private:
	Board board;
	sf::Clock clock;
	sf::Text timerText;
	sf::Font font;
};


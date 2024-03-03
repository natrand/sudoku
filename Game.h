#pragma once

#include "Board.h"

class Game
{
public:
	Game();

	void update(sf::RenderWindow& window);
	void StartGame();
	Board& getBoard();
private:
	Board board;
};


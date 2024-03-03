#include "Game.h"
#include "Board.h"
#include <iostream>


Game::Game() {

	if (!font.loadFromFile("assets/joystix monospace.otf"))
	{
		std::cout << "Error: Font loading failed." << std::endl;
	}

	timerText.setFont(font); 
	timerText.setCharacterSize(24);
	timerText.setFillColor(sf::Color(200, 156, 162));
	timerText.setPosition(550, 10);

}
Board& Game::getBoard() {
	return board;
}

void Game::update(sf::RenderWindow& window) {

	const std::vector<std::vector<int>>& currentBoard = board.getSudokuBoard();
	board.updateNumbers(currentBoard,window);
	// Update the timer
	sf::Time elapsed = clock.getElapsedTime();
	int seconds = elapsed.asSeconds();
	int minutes = seconds / 60;
	seconds %= 60;

	// Update the timer text
	setTimerText("Time: " + std::to_string(minutes) + ":" + std::to_string(seconds));

}

void Game::StartGame() {

	board.GenerateRandomNumbers();

}

void Game::draw(sf::RenderWindow& window) {
	board.draw(window);
	window.draw(timerText);
}

void Game::startTimer() {
	clock.restart();
}

void Game::setTimerText(const std::string& text) {
	timerText.setString(text);

}
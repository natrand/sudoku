#include "Game.h"
#include "Board.h"


Game::Game() {


}
Board& Game::getBoard() {
	return board;
}

void Game::update(sf::RenderWindow& window) {

	const std::vector<std::vector<int>>& currentBoard = board.getSudokuBoard();
	board.updateNumbers(currentBoard,window);
}

void Game::StartGame() {

	board.GenerateRandomNumbers();

}

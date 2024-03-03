#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Menu.h"
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SUDOKU");

    window.clear(sf::Color(65,36,40));

    Board sudokuboard;
    Game game;
    game.getBoard().GenerateRandomNumbers();
    game.startTimer();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color(65, 36, 40));
        sudokuboard.draw(window);
        game.draw(window);
        game.update(window);

        window.display();
    }

    return 0;
}

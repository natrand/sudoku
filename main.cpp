#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Menu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SUDOKU");

    window.clear(sf::Color(65,36,40));

    Board sudokuboard;

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
        window.display();
    }

    return 0;
}

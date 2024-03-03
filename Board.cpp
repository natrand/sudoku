#include "Board.h"
#include <cstdlib>
#include <iostream>
#include <random>


Board::Board()
{
    bigRectSize = sf::Vector2f(200, 200);
    bigRectColor = sf::Color(164, 90, 101); // #a45a65
    smallRectSize = sf::Vector2f(60, 60);
    smallGap = 5.0f;
    gap = 50.0f;

    if (!font.loadFromFile("assets/joystix monospace.otf"))
    {
        std::cout << "Error: Font loading failed." << std::endl;
    }


    // Calculate total width of the grid
    float totalWidth = 3 * (bigRectSize.x + gap) - gap;

    // Calculate starting x position to center the grid horizontally
    float startX = (800 - totalWidth) / 2;

    // Create big rectangles and position them
    for (int i = 0; i < 9; ++i)
    {
        bigRectangles[i].setSize(bigRectSize);
        bigRectangles[i].setFillColor(bigRectColor);

        // Calculate position based on row and column index
        int row = i / 3;
        int col = i % 3;
        float x = startX + col * (bigRectSize.x + gap);
        float y = row * (bigRectSize.y + gap) + gap;
        bigRectangles[i].setPosition(x, y);

        // Create small rectangles within each big rectangle
        float startXSmall = bigRectangles[i].getPosition().x + smallGap;
        float startYSmall = bigRectangles[i].getPosition().y + smallGap;
        for (int j = 0; j < 9; ++j)
        {
            smallRectangles[i][j].setSize(smallRectSize);
            smallRectangles[i][j].setFillColor(sf::Color(200, 156, 162));

            int innerRow = j / 3;
            int innerCol = j % 3;
            float xSmall = startXSmall + innerCol * (smallRectSize.x + smallGap);
            float ySmall = startYSmall + innerRow * (smallRectSize.y + smallGap);
            smallRectangles[i][j].setPosition(xSmall, ySmall);
        }
    }
}

void Board::draw(sf::RenderWindow& window)
{
    // Draw big rectangles
    for (int i = 0; i < 9; ++i)
    {
        window.draw(bigRectangles[i]);
    }

    // Draw small rectangles within each big rectangle
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            window.draw(smallRectangles[i][j]);
        }
    }
}

void Board::GenerateRandomNumbers() {

    std::random_device rd;
    std::mt19937 gen(rd());

    SudokuBoard.clear();

    for (int i = 0; i < 9; i++) {
        std::vector<int> row;
        for (int j = 0; j < 9; j++) {
            std::uniform_int_distribution<int> dis(1, 9);
            int num = dis(gen);
            row.push_back(num);
        }
        SudokuBoard.push_back(row);
    }
}

void Board::updateNumbers(const std::vector<std::vector<int>>& SudokuBoard, sf::RenderWindow& window) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int value = SudokuBoard[i][j];
            sf::RectangleShape& smallRect = smallRectangles[i][j];

            float offsetX = (smallRectSize.x - textSize) / 2;
            float offsetY = (smallRectSize.y - textSize) / 2;

            // Create SFML text object to display the number
            sf::Text text(std::to_string(value), font, textSize);
            text.setPosition(smallRect.getPosition().x + offsetX, smallRect.getPosition().y + offsetY);
            text.setFillColor(sf::Color::Black); // Set text color (you can change it as needed)

            // Draw the text on the window
            window.draw(text);
        }
    }

}

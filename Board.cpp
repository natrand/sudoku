#include "Board.h"

Board::Board()
{
    bigRectSize = sf::Vector2f(200, 200);
    bigRectColor = sf::Color(164, 90, 101); // #a45a65
    smallRectSize = sf::Vector2f(60, 60);
    smallGap = 5.0f;
    gap = 50.0f;

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

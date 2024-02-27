#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Sudoku Board");

    sf::Vector2f rectSize(200, 200);
    sf::Color rectColor(sf::Color::Red);
    sf::Color whiteColor(sf::Color::White);

    // Define the size and gap of small white rectangles within each red rectangle
    sf::Vector2f smallRectSize(60, 60);
    float smallGap = 5.0f;
    float gap = 50.0f;

    // Create red rectangles and position them
    sf::RectangleShape redRectangles[9];
    for (int i = 0; i < 9; ++i)
    {
        redRectangles[i].setSize(rectSize);
        redRectangles[i].setFillColor(rectColor);

        // Calculate position based on row and column index
        int row = i / 3;
        int col = i % 3;
        float x = col * (rectSize.x + gap) + gap;
        float y = row * (rectSize.y + gap) + gap;
        redRectangles[i].setPosition(x, y);
    }

    // Create white small rectangles within each red rectangle
    sf::RectangleShape whiteRectangles[9][9];
    for (int i = 0; i < 9; ++i)
    {
        // Calculate position for small rectangles within each red rectangle
        int row = i / 3;
        int col = i % 3;
        float startX = redRectangles[i].getPosition().x + smallGap;
        float startY = redRectangles[i].getPosition().y + smallGap;
        for (int j = 0; j < 9; ++j)
        {
            whiteRectangles[i][j].setSize(smallRectSize);
            whiteRectangles[i][j].setFillColor(whiteColor);

            int innerRow = j / 3;
            int innerCol = j % 3;
            float x = startX + innerCol * (smallRectSize.x + smallGap);
            float y = startY + innerRow * (smallRectSize.y + smallGap);
            whiteRectangles[i][j].setPosition(x, y);
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Draw red rectangles
        for (int i = 0; i < 9; ++i)
        {
            window.draw(redRectangles[i]);
        }

        // Draw white small rectangles within each red rectangle
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                window.draw(whiteRectangles[i][j]);
            }
        }

        window.display();
    }

    return 0;
}

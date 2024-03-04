#include "Board.h"
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>


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
    SudokuBoard.resize(9, std::vector<int>(9, 0)); // Initialize Sudoku board with zeros

    // Call the backtracking function to generate a valid Sudoku board
    if (!generateSudokuBoard(0, 0)) {
        std::cerr << "Error: Failed to generate Sudoku board." << std::endl;
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

bool Board::isSafe() const {
    // Check each row, column, and 3x3 board
    for (int i = 0; i < 9; ++i) {
        std::vector<bool> rowVisited(9);
        std::vector<bool> colVisited(9);
        std::vector<bool> boardVisited(9);

        for (int j = 0; j < 9; ++j) {
            // Check row
            int rowNum = SudokuBoard[i][j];
            if (rowNum < 1 || rowNum > 9) {
                continue; // Skip invalid numbers
            }
            if (rowVisited[rowNum - 1]) {
                return false; // Duplicate number found in row
            }
            rowVisited[rowNum - 1] = true;

            // Check column
            int colNum = SudokuBoard[j][i];
            if (colNum < 1 || colNum > 9) {
                continue; // Skip invalid numbers
            }
            if (colVisited[colNum - 1]) {
                return false; // Duplicate number found in column
            }
            colVisited[colNum - 1] = true;

            // Check 3x3 board
            int startRow = 3 * (i / 3);
            int startCol = 3 * (i % 3);
            int boardNum = SudokuBoard[startRow + j / 3][startCol + j % 3];
            if (boardNum < 1 || boardNum > 9) {
                continue; // Skip invalid numbers
            }
            if (boardVisited[boardNum - 1]) {
                return false; // Duplicate number found in 3x3 board
            }
            boardVisited[boardNum - 1] = true;
        }
    }

    return true; // Board is safe
}


bool Board::generateSudokuBoard(int row, int col) {
    if (row == 9) {
        return true; // All rows filled, Sudoku board generated successfully
    }

    // Calculate next row and column indices
    int nextRow = (col == 8) ? row + 1 : row;
    int nextCol = (col + 1) % 9;

    // Try placing numbers 1 to 9 in the current cell
    for (int num = 1; num <= 9; ++num) {
        // Check if the current number is valid in the current cell
        if (isValidMove(row, col, num)) {
            SudokuBoard[row][col] = num;

            // Recursively try filling the next cell
            if (generateSudokuBoard(nextRow, nextCol)) {
                return true; // Sudoku board generated successfully
            }

            // Backtrack if the current configuration doesn't lead to a valid solution
            SudokuBoard[row][col] = 0;
        }
    }

    return false; // No valid number found for the current cell
}

bool Board::isValidMove(int row, int col, int num) const {
    // Check if the number is already present in the current row or column
    for (int i = 0; i < 9; ++i) {
        if (SudokuBoard[row][i] == num || SudokuBoard[i][col] == num) {
            return false; // Number already present in row or column
        }
    }

    // Check if the number is already present in the current 3x3 subgrid
    int startRow = 3 * (row / 3);
    int startCol = 3 * (col / 3);
    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startCol; j < startCol + 3; ++j) {
            if (SudokuBoard[i][j] == num) {
                return false; // Number already present in 3x3 subgrid
            }
        }
    }

    return true; // Move is valid
}
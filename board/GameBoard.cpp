//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#include "GameBoard.h"

GameBoard::GameBoard(int boardWidth, int boardHeight) {
  gameBoard = createEmptyGameBoard(boardWidth, boardHeight);
}

void GameBoard::showBoard() {
  int width = gameBoard.size();
  int height = gameBoard[0].size();

  // Calculate the max length of an index on the board, so that each index can
  // be padded to the same length and the board can be evenly spaced.
  int maxWidthLength = getAsciiLabel(width - 1).length();
  int maxHeightLength = std::to_string(height).length();
  int maxIndexLength = std::max(maxWidthLength, maxHeightLength) + PADDING;

  // Start from -1 to account for the coordinate labels.
  for (int y = -1; y < height; y++) {
    for (int x = -1; x < width; x++) {
      std::string indexString;
      if (x == -1 && y == -1) { // Top left corner.
        indexString = ""; // Show an empty index.
      } else if (y == -1) { // Top row, for the coordinate labels.
        indexString = getAsciiLabel(x); // Use letters to represent the columns.
      } else if (x == -1) { // Left column, for the coordinate labels.
        indexString = std::to_string(y+1); // Use numbers to represent rows.
      } else { // Game board.
        indexString = gameBoard[x][y]; // Show the current game board index.
      }
      std::cout << padString(indexString, maxIndexLength);
    }
    std::cout << std::endl;
  }
}

std::vector<std::vector<std::string>> GameBoard::createEmptyGameBoard(int boardWidth, int boardHeight) {
  std::vector<std::vector<std::string>> gameBoard;

  for (int x = 0; x < boardWidth; x++) {
    std::vector<std::string> row; // Create a vector to represent this row.
    row.reserve(boardHeight); // Pre-allocate the capacity used by the for loop.
    for (int y = 0; y < boardHeight; y++) {
      row.emplace_back("0"); // Add an empty board state to this index.
    }
    gameBoard.push_back(row); // Add this row to the game board.
  }

  return gameBoard;
}

std::string GameBoard::getAsciiLabel(int number) {
  std::string string;

  while (number >= 0) {
    string = (char)('A' + number % 26 ) + string; // Get the right-most letter and place it in the string.
    number = number / 26; // Right shift to get the next letter.
    number--;
  }

  return string;
}

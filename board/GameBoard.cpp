//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#include "GameBoard.h"

GameBoard::GameBoard(int boardWidth, int boardHeight) {
  gameBoard = createEmptyGameBoard(boardWidth, boardHeight);
}

void GameBoard::showBoard() {
  for (int x = 0; x < gameBoard.size(); x++) {
    for (int y = 0; y < gameBoard[x].size(); y++) {
        std::cout << gameBoard[x][y]; // Print out this index.
    }
    std::cout << std::endl; // Start the next line.
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



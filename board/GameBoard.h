//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#ifndef BATTLESHIPS_BOARD_GAMEBOARD_H_
#define BATTLESHIPS_BOARD_GAMEBOARD_H_

class GameBoard {

  const int PADDING = 2; // Padding so each index can be bigger than the max index length.

  std::vector<std::vector<std::string>> gameBoard; // Use a 2D vector to represent the game board.

private:
  static std::vector<std::vector<std::string>> createEmptyGameBoard(int boardWidth, int boardHeight);

  static std::string getAsciiLabel(int number);

public:
  GameBoard(int boardWidth, int boardHeight); // Constructor that takes the board dimensions.

  void showBoard();
};

#endif // BATTLESHIPS_BOARD_GAMEBOARD_H_

//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#ifndef BATTLESHIPS_BOARD_GAMEBOARD_H_
#define BATTLESHIPS_BOARD_GAMEBOARD_H_

class GameBoard {

  std::vector<std::vector<std::string>> gameBoard; // Use a 2D vector to represent the game board.

private:
  static std::vector<std::vector<std::string>> createEmptyGameBoard(int boardWidth, int boardHeight);

public:
  GameBoard(int boardWidth, int boardHeight); // Constructor that takes the board dimensions.

  void showBoard();
};

#endif // BATTLESHIPS_BOARD_GAMEBOARD_H_

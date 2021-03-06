//
// Created by Bhupinder Dhoofer on 13/03/2021.
//

#ifndef BATTLESHIPS_BOARD_HITBOARD_H_
#define BATTLESHIPS_BOARD_HITBOARD_H_

#include <utility>

class HitBoard {

public:
  HitBoard(std::string playerName); // Constructor.

  void showBoard();

  void updateBoard(const Coordinate& torpedoLocation, HitStatus hitStatus);

  bool isValidLocation(const Coordinate& torpedoLocation);

private:

  std::string playerName;

  std::string HIT_STATE = "H";
  std::string MISS_STATE = "M";

  std::vector<std::vector<std::string>> hitBoard; // Use a 2D vector to represent the hit board.

};

#endif // BATTLESHIPS_BOARD_HITBOARD_H_

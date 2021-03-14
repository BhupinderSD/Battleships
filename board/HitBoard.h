//
// Created by Bhupinder Dhoofer on 13/03/2021.
//

#ifndef BATTLESHIPS_BOARD_HITBOARD_H_
#define BATTLESHIPS_BOARD_HITBOARD_H_

class HitBoard {

public:
  HitBoard(); // Constructor.

  void showBoard();

  void updateBoard(const Coordinate& torpedoLocation, bool hitStatus);

private:

  std::string HIT_STATE = "H";
  std::string MISS_STATE = "M";

  std::vector<std::vector<std::string>> hitBoard; // Use a 2D vector to represent the hit board.

};

#endif // BATTLESHIPS_BOARD_HITBOARD_H_

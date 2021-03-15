//
// Created by Bhupinder Dhoofer on 13/03/2021.
//

#include "HitBoard.h"

HitBoard::HitBoard() {
  hitBoard = ::createEmptyBoard();
}

void HitBoard::showBoard() {
  std::cout << "Hit board." << std::endl;
  ::showBoard(hitBoard);
}

void HitBoard::updateBoard(const Coordinate &torpedoLocation, HitStatus hitStatus) {
  switch (hitStatus) {
  case HIT:
    std::cout << "Hit!" << std::endl;
    ::setBoardIndexWithString(hitBoard, torpedoLocation, HIT_STATE);
    break;
  case SUNK:
    std::cout << "Hit and sunk a ship!" << std::endl;
    ::setBoardIndexWithString(hitBoard, torpedoLocation, HIT_STATE);
    break;
  case WIN:
    std::cout << "You win!" << std::endl;
    //TODO(Bhupinder): End the game at a win.
    break;
  case MISS:
    std::cout << "Miss!" << std::endl;
    ::setBoardIndexWithString(hitBoard, torpedoLocation, MISS_STATE);
    break;
  }
}

/** Returns true if this position has not been fired at previously. */
bool HitBoard::isValidLocation(const Coordinate &torpedoLocation) {
  std::string index = ::getBoardIndex(hitBoard, torpedoLocation);

  if (index == ::EMPTY_STATE) {
    return true;
  }

  return false;
}

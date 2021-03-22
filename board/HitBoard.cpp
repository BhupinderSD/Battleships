//
// Created by Bhupinder Dhoofer on 13/03/2021.
//

#include "HitBoard.h"

HitBoard::HitBoard(std::string playerName) {
  this->playerName = std::move(playerName);
  hitBoard = ::createEmptyBoard();
}

void HitBoard::showBoard() {
  std::cout << playerName << " - Hit board." << std::endl;
  ::showBoard(hitBoard);
}

void HitBoard::updateBoard(const Coordinate &torpedoLocation, HitStatus hitStatus) {
  switch (hitStatus) {
  case HIT:
    std::cout << playerName << " - Hit!" << std::endl;
    ::setBoardIndexWithString(hitBoard, torpedoLocation, HIT_STATE);
    break;
  case SUNK:
    std::cout << playerName << " - Hit and sunk a ship!" << std::endl;
    ::setBoardIndexWithString(hitBoard, torpedoLocation, HIT_STATE);
    break;
  case WIN:
    std::cout << playerName << " - You win!" << std::endl;
    ::setBoardIndexWithString(hitBoard, torpedoLocation, HIT_STATE);
    break;
  case MISS:
    std::cout << playerName << " - Miss!" << std::endl;
    ::setBoardIndexWithString(hitBoard, torpedoLocation, MISS_STATE);
    break;
  case MINE:
    std::cout << playerName << " - Hit a mine!" << std::endl;
    setMineHit(hitBoard, torpedoLocation, HIT_STATE);
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

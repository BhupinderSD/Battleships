//
// Created by Bhupinder Dhoofer on 12/03/2021.
//

#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer() {
  gameBoard.autoPlaceUnplacedBoats();
  gameBoard.showBoard();
}

Coordinate ComputerPlayer::nextTurn() {
  Coordinate fireTorpedoLocation = gameBoard.getRandomCoordinates();
  std::cout << fireTorpedoLocation.x << std::to_string(fireTorpedoLocation.y) << std::endl;
  return fireTorpedoLocation;
}

void ComputerPlayer::updateIfHit(const Coordinate& torpedoLocation) {
    if (gameBoard.isHit(torpedoLocation)) {
    std::cout << "Hit!" << std::endl;
    //TODO(Bhupinder): Update hit board.
  } else {
    std::cout << "Miss!" << std::endl;
  }
}

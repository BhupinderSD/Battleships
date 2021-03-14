//
// Created by Bhupinder Dhoofer on 12/03/2021.
//

#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer() {
  gameBoard.autoPlaceUnplacedBoats();
  gameBoard.showBoard();
}

Coordinate ComputerPlayer::nextTurn() {
  gameBoard.showBoard(); // Show the current game board.
  hitBoard.showBoard(); // Show the current hit board.
  Coordinate fireTorpedoLocation = gameBoard.getRandomCoordinates();
  std::cout << fireTorpedoLocation.x << std::to_string(fireTorpedoLocation.y) << std::endl;
  return fireTorpedoLocation;
}

HitStatus ComputerPlayer::getHitStatus(const Coordinate& torpedoLocation) {
  return gameBoard.getHitStatus(torpedoLocation);
}

void ComputerPlayer::updateHitBoard(const Coordinate &torpedoLocation, HitStatus hitStatus) {
  hitBoard.updateBoard(torpedoLocation, hitStatus);
}

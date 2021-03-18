//
// Created by Bhupinder Dhoofer on 12/03/2021.
//

#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer() {
  placeBoats();
}

Coordinate ComputerPlayer::nextTurn() {
  gameBoard.showBoard(); // Show the current game board.
  hitBoard.showBoard(); // Show the current hit board.

  Coordinate fireTorpedoLocation = getFireLocation();

  std::cout << fireTorpedoLocation.x << std::to_string(fireTorpedoLocation.y + 1) << std::endl;
  return fireTorpedoLocation;
}

HitStatus ComputerPlayer::getHitStatus(const Coordinate& torpedoLocation) {
  return gameBoard.getHitStatus(torpedoLocation);
}

void ComputerPlayer::updateHitBoard(const Coordinate &torpedoLocation, HitStatus hitStatus) {
  hitBoard.updateBoard(torpedoLocation, hitStatus);
}

void ComputerPlayer::placeBoats() {
  gameBoard.autoPlaceUnplacedBoats(); // Try to place all boats.
  gameBoard.showBoard();

  while (gameBoard.hasUnplacedBoats()) { // If any boats couldn't be placed, ask the user how to proceed.
    int option = getNumber("Unable to place all boats. Please choose an option:\n0. Try again\n1. Reset board and try again\n2. Continue ", 0, 2);

    switch (option) {
    case 0:
      gameBoard.autoPlaceUnplacedBoats();
      gameBoard.showBoard();
      continue;
    case 1:
      gameBoard.resetGameBoard();
      gameBoard.autoPlaceUnplacedBoats();
      gameBoard.showBoard();
      continue;
    case 2:
      break;
    default:
      std::cout << "Invalid input, please try again.";
    }
  }
}

Coordinate ComputerPlayer::getFireLocation() {
  Coordinate fireTorpedoLocation;

  while (true) { // Keep generating coordinates till we receive a valid/unused location.
    fireTorpedoLocation = gameBoard.getRandomCoordinates();

    if (hitBoard.isValidLocation(fireTorpedoLocation)) {
      break;
    }
  }

  return fireTorpedoLocation;
}
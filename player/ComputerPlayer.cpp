//
// Created by Bhupinder Dhoofer on 12/03/2021.
//

#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer(const std::string &playerName): Player(playerName) {
  placeBoats();
}

Coordinate ComputerPlayer::nextTurn() {
  std::cout << playerName <<  "." << std::endl;

  gameBoard.showBoard(); // Show the current game board.
  hitBoard.showBoard(); // Show the current hit board.

  Coordinate fireTorpedoLocation = getFireLocation();

  return fireTorpedoLocation;
}

HitStatus ComputerPlayer::getHitStatus(const Coordinate& torpedoLocation) {
  return gameBoard.getHitStatus(torpedoLocation);
}

void ComputerPlayer::updateHitBoard(const Coordinate &torpedoLocation, HitStatus hitStatus) {
  hitBoard.updateBoard(torpedoLocation, hitStatus);
}

void ComputerPlayer::waitToEndTurn() {
  ::waitForUser("Press enter to end the " + playerName + "'s turn.\n");
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
 return ::getAutoFireLocation(gameBoard, hitBoard);
}
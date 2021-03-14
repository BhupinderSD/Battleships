//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer() {}

void HumanPlayer::setBoatsOnBoard() {
  while (true) {
    selectAndSetBoatsOnBoard();

    int option = getNumber("Are you happy with the boat placements? \n1. Yes\n2. Move a boat\n3. Reset the board", 1, 3);
    switch (option) {
    case 1:
      return; // If the user is happy with the boat placements, continue with the game.
    case 2:
      continue; // Show the user the placed boats and let them move one boat each time.
    case 3:
      gameBoard.resetGameBoard(); // Reset the game board.
      continue; // Continue with the loop and place all of the boats again.
    default:
      std::cout << "Invalid option, please try again." << std::endl;
      continue;
    }
  }
}

Coordinate HumanPlayer::nextTurn() {
  gameBoard.showBoard(); // Show the users current game board.
  hitBoard.showBoard(); // Show the users current hit board.
  return gameBoard.getCoordinates("What coordinates do you want to fire a torpedo at?");
}

HitStatus HumanPlayer::getHitStatus(const Coordinate &torpedoLocation) {
  return gameBoard.getHitStatus(torpedoLocation);
}

void HumanPlayer::updateHitBoard(const Coordinate &torpedoLocation, HitStatus hitStatus) {
  hitBoard.updateBoard(torpedoLocation, hitStatus);
}

void HumanPlayer::selectAndSetBoatsOnBoard() {
  std::map<std::string, int> boatMap = configSingleton.getBoatMap();
  std::vector<std::string> boatNames = configSingleton.getBoatNames();

  do { // Allow the user to replace a boat, even if all boats are placed.
    gameBoard.showPlacedAndUnplacedBoats();

    int option = getNumber("Please enter the number of the boat to place: ", 0, boatNames.size());
    if (option == 0) { // Auto-place all remaining boats.
      gameBoard.autoPlaceUnplacedBoats();
      gameBoard.showBoard();
      continue;
    }

    std::string boatName = boatNames[option - 1];
    int boatLength = boatMap.find(boatName)->second;

    gameBoard.setBoatOnBoard(boatName, boatLength); // Place every boat on the board.
    gameBoard.showBoard();
  } while (gameBoard.hasUnplacedBoats());
}
//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(const std::string &playerName): Player(playerName) {
  placeBoats();
}

Coordinate HumanPlayer::nextTurn() {
  std::cout << playerName <<  "." << std::endl;

  gameBoard.showBoard(); // Show the users current game board.
  hitBoard.showBoard(); // Show the users current hit board.

  while (true) {
    int option = getNumber(playerName + " - How would you like to take your next turn:\n0. Auto fire\n1. Enter coordinates ", 0, 1);
    switch (option) {
    case 0:
      return ::getAutoFireLocation(gameBoard, hitBoard, playerName);
    case 1:
      return getFireLocation();
    default:
      std::cout << "Invalid input, please try again.";
    }
  }
}

HitStatus HumanPlayer::getHitStatus(const Coordinate &torpedoLocation) {
  return gameBoard.getHitStatus(torpedoLocation);
}

void HumanPlayer::updateHitBoard(const Coordinate &torpedoLocation, HitStatus hitStatus) {
  hitBoard.updateBoard(torpedoLocation, hitStatus);
}

void HumanPlayer::waitToEndTurn() {
  ::waitForUser(playerName + " - Press enter to end this turn.\n");
}

void HumanPlayer::placeBoats() {
  while (true) {
    selectAndSetBoatsOnBoard();

    int option = getNumber(playerName + " - Are you happy with the boat placements? \n1. Yes\n2. Move a boat\n3. Reset the board", 1, 3);
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

void HumanPlayer::selectAndSetBoatsOnBoard() {
  std::map<std::string, int> boatMap = configSingleton.getBoatMap();
  std::vector<std::string> boatNames = configSingleton.getBoatNames();

  do { // Allow the user to replace a boat, even if all boats are placed.
    gameBoard.showPlacedAndUnplacedBoats();

    int option = getNumber(playerName + " - Please enter the number of the boat to place: ", 0, boatNames.size());
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

Coordinate HumanPlayer::getFireLocation() {
  Coordinate coordinate;
  while (true) { // Keep asking the user for coordinates till we receive a valid/unused location.
    coordinate = gameBoard.getCoordinates(playerName + " - What coordinates do you want to fire a torpedo at?");

    if (hitBoard.isValidLocation(coordinate)) {
      break;
    }

    std::cout << playerName << " - You have already fired at this location, please try again." << std::endl;
  }

  return coordinate;
}

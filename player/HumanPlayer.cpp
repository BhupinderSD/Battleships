//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer() {}

void HumanPlayer::setBoatsOnBoard() {
  for (auto &itr : boatsMap) { // Iterate though every boat in the map.
    setBoatOnBoard(itr.first, itr.second); // Place every boat on the board.
  }
  gameBoard.showBoard();

  if (getNumber("Are you happy with the boat placements? \n1. Continue") == 1) {
    return;
  }
}

void HumanPlayer::setBoatOnBoard(const std::string& boatName, int boatLength) {
  while (true) { // Keep asking the user where they want to place a boat until we get a valid position.
    BoatStart boatStart;

    gameBoard.showBoard();
    boatStart.orientation = getOrientation(boatName);

    gameBoard.showBoard();
    boatStart.coordinate = getCoordinates(boatName);

    if (gameBoard.maybePlaceBoat(boatName, boatLength, boatStart)) {
      break; // Once we have placed the boat on the board, exit the loop.
    }
  }
}

Orientation HumanPlayer::getOrientation(const std::string& boatName) {
  std::string question = "Which way do you want to place " + boatName + "? \n 1. Horizontally \n 2. Vertically \n";
  int orientation;

  std::cout << question; // Show the user the question.
  std::cin >> orientation; // Get the users response.
  while(std::cin.fail() || (orientation != 1 && orientation != 2)) { // While the user enters an invalid input, keep asking for an orientation.
    std::cout << "Please enter a valid orientation.\n\n";
    flushBuffer();
    std::cout << question;
    std::cin >> orientation;
  }
  flushBuffer();

  if (orientation == 1) {
    return Orientation::HORIZONTAL;
  } else {
    return Orientation::VERTICAL;
  }
}

Coordinate HumanPlayer::getCoordinates(const std::string &boatName) {
  Coordinate coordinate;

  while (true) { // Ask for coordinates till we receive valid coordinates.
    Coordinate tempCoordinates;
    std::string userCoordinates = getLine("Where do you want to place " + boatName + "? ");

    // Split the x and y coordinates.
    for (char character : userCoordinates) {
      if (isalpha(character)) {
        tempCoordinates.x += character;
      } else if (isdigit(character)) {
        tempCoordinates.y = tempCoordinates.y * 10 + (character - '0');
      }
    }

    // Check that the coordinates are valid.
    if (tempCoordinates.x.empty() && tempCoordinates.y == 0) {
      std::cout << "Please enter valid coordinates.\n" << std::endl;
    } else if (tempCoordinates.x.empty()) {
      std::cout << "Please enter a valid x coordinate (a letter).\n" << std::endl;
    } else if (tempCoordinates.y == 0) {
      std::cout << "Please enter a valid y coordinate (a number).\n" << std::endl;
    } else {
      tempCoordinates.y = tempCoordinates.y - 1; // Subtract 1 since the board index starts at 0.
      coordinate = tempCoordinates; // Set the temp coordinates as the coordinates to return.
      break;
    }
  }

  return coordinate;
}

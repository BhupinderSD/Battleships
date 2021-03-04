//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer() {}

void HumanPlayer::setBoats(const std::map<std::string, int>& boatsMap) {
  for (auto &itr : boatsMap) { // Iterate though every boat in the map.
    std::string boatName = itr.first;
    BoatPosition boatPosition;
    boatPosition.orientation = getOrientation(boatName);
    boatPosition.coordinate = getCoordinates(boatName);
  }
}

HumanPlayer::Orientation HumanPlayer::getOrientation(const std::string& boatName) {
  std::string question = "Which way do you want to place " + boatName + "? \n 1. Landscape \n 2. Portrait \n";
  int orientation;

  std::cout << question; // Show the user the question.
  std::cin >> orientation; // Get the users response.
  while(std::cin.fail() || orientation != 1 && orientation != 2) { // While the user enters an invalid input, keep asking for an orientation.
    std::cout << "Please enter a valid orientation.\n\n";
    flushBuffer();
    std::cout << question;
    std::cin >> orientation;
  }
  flushBuffer();

  if (orientation == 1) {
    return HumanPlayer::Orientation::LANDSCAPE;
  } else {
    return HumanPlayer::Orientation::PORTRAIT;
  }
}

HumanPlayer::Coordinate HumanPlayer::getCoordinates(const std::string &boatName) {
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
      std::cout << "Please enter valid BoatPosition.\n" << std::endl;
    } else if (tempCoordinates.x.empty()) {
      std::cout << "Please enter a valid x boatPosition (a letter).\n" << std::endl;
    } else if (tempCoordinates.y == 0) {
      std::cout << "Please enter a valid y boatPosition (a number).\n" << std::endl;
    } else {
      coordinate = tempCoordinates; // Set the temp coordinates as the coordinates to return.
      break;
    }
  }

  return coordinate;
}

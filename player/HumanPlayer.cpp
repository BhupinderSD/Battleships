//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer() {}

void HumanPlayer::setBoatsOnBoard() {
  while (true) {
    selectAndSetBoatsOnBoard();
    gameBoard.showBoard();

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

void HumanPlayer::selectAndSetBoatsOnBoard() {
  std::map<std::string, int> boatMap = configSingleton.getBoatMap();
  std::vector<std::string> boatNames = configSingleton.getBoatNames();

  do { // Allow the user to replace a boat, even if all boats are placed.
    gameBoard.showPlacedAndUnplacedBoats();

    int option = getNumber("Please enter the number of the boat to place: ", 0, boatNames.size());
    if (option == 0) { // Auto-place all remaining boats.
      gameBoard.autoPlaceUnplacedBoats();
      continue;
    }

    std::string boatName = boatNames[option - 1];
    int boatLength = boatMap.find(boatName)->second;

    setBoatOnBoard(boatName, boatLength); // Place every boat on the board.
  } while (gameBoard.hasUnplacedBoats());
}

void HumanPlayer::setBoatOnBoard(const std::string& boatName, int boatLength) {
  while (true) { // Keep asking the user where they want to place a boat until we get a valid position.
    gameBoard.removeBoatFromBoardIfPlaced(boatName);

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
  int orientation = getNumber(question, 1, 2);

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

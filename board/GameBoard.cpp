//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#include "GameBoard.h"

GameBoard::GameBoard() {
  initRandom();
  gameBoard = ::createEmptyBoard();
}

void GameBoard::showBoard() {
  std::cout << "Game board." << std::endl;
  ::showBoard(gameBoard);
}

void GameBoard::showPlacedAndUnplacedBoats() {
  std::vector<std::string> boatNames = configSingleton.getBoatNames();
  std::vector<std::string> unplacedBoats;
  std::vector<std::string> placedBoats;

  for (int i = 0; i < boatNames.size(); i++) {
    std::string indexString = std::to_string(i + 1) + ". ";
    if (boatLocations.find(boatNames[i]) == boatLocations.end()) { // If the boat was not found.
      unplacedBoats.push_back(indexString + boatNames[i]); // Add the boat to the unplaced boats vector.
    } else { // If the boat was found.
      placedBoats.push_back(indexString + boatNames[i]);// Add the boat to the placed boats vector.
    }
  }

  if (!unplacedBoats.empty()) {
    unplacedBoats.push_back(std::to_string(0) + ". Auto-place unplaced boats."); // Inform the user that they can auto-place boats.
  }

  printList("Placed boats:", placedBoats);
  printList("Unplaced boats:", unplacedBoats);
}

void GameBoard::autoPlaceUnplacedBoats() {
  std::map<std::string, int> boatMap = configSingleton.getBoatMap();
  std::vector<std::string> boatNames = configSingleton.getBoatNames();
  std::vector<std::string> unplacedBoats;

  for (auto &boatName : boatNames) { // Find all of the unplaced boats and store the names in a vector.
    if (boatLocations.find(boatName) == boatLocations.end()) { // If the boat has not been placed on the board.
      unplacedBoats.push_back(boatName); // Add the boat to the unplaced boats vector.
    }
  }

  for (auto &boatName : unplacedBoats) { // Try to add every unplaced boat on the board.
    int boatLength = boatMap.find(boatName)->second;

    int loopCount = 0;
    while (true) { // Keep trying to place the boat until we get a valid position.
      BoatStart boatStart;
      boatStart.orientation = randomBoolean(rng) ? Orientation::HORIZONTAL : Orientation::VERTICAL; // Choose a random orientation.
      boatStart.coordinate = getRandomCoordinates();

      if (maybePlaceBoat(boatName, boatLength, boatStart, /* printErrors= */ false)) { // Try to place the boat without printing any errors.
        break; // Once we have placed the boat on the board, exit the loop.
      }

      if (loopCount > boardHeight * boardWidth * 2) { // Don't try to place a boat an unnecessary number of times.
        std::cout << "Couldn't automatically place " << boatName << "." << std::endl; // Inform the user that a boat couldn't be placed automatically.
        break; // Break the while true and try to place the next boat.
      }

      loopCount++; // Increment the loop count.
    }
  }
}

Coordinate GameBoard::getRandomCoordinates() {
  Coordinate coordinate;
  coordinate.x = ::getAsciiLabel(randomWidth(rng)); // Choose a random x coordinate.
  coordinate.y = randomHeight(rng); // Choose a random y coordinate.
  return coordinate;
}

void GameBoard::setBoatOnBoard(const std::string& boatName, int boatLength) {
  while (true) { // Keep asking the user where they want to place a boat until we get a valid position.
    removeBoatFromBoardIfPlaced(boatName);

    BoatStart boatStart;

    showBoard();
    boatStart.orientation = getOrientation(boatName);

    showBoard();
    boatStart.coordinate = getCoordinates("Where do you want to place " + boatName + "? ");

    if (maybePlaceBoat(boatName, boatLength, boatStart, /* printErrors= */ true)) {
      break; // Once we have placed the boat on the board, exit the loop.
    }
  }
}

bool GameBoard::hasUnplacedBoats() {
  for (const std::string& boatName : configSingleton.getBoatNames()) {
    if (boatLocations.find(boatName) == boatLocations.end()) { // If the boat has not been placed.
      return true; // Return true, meaning that this boat has not been placed yet.
    }
  }

  return false; // All boats have been placed.
}

void GameBoard::removeBoatFromBoardIfPlaced(const std::string &boatName) {
  if (boatLocations.find(boatName) == boatLocations.end()) {
    return; // If the boat has not been placed, return.
  }

  std::vector<Coordinate> boatCoordinates = boatLocations.find(boatName)->second; // Coordinates that this boat occupies.

  for (const Coordinate& coordinate : boatCoordinates) {
    ::setBoardIndexWithString(gameBoard, coordinate, ::EMPTY_STATE);
  }
}

Orientation GameBoard::getOrientation(const std::string& boatName) {
  std::string question = "Which way do you want to place " + boatName + "? \n 1. Horizontally \n 2. Vertically \n";
  int orientation = getNumber(question, 1, 2);

  if (orientation == 1) {
    return Orientation::HORIZONTAL;
  } else {
    return Orientation::VERTICAL;
  }
}

Coordinate GameBoard::getCoordinates(const std::string &request) {
  Coordinate coordinate;

  while (true) { // Ask for coordinates till we receive valid coordinates.
    Coordinate tempCoordinates;
    std::string userCoordinates = getLine(request);

    // Split the x and y coordinates.
    for (char character : userCoordinates) {
      if (isalpha(character)) {
        tempCoordinates.x += toupper(character);
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
    } else if (!isValidCoordinate(tempCoordinates)) {
      std::cout << "Please enter valid coordinates within the bounds of the board.\n" << std::endl;
    } else {
      tempCoordinates.y = tempCoordinates.y - 1; // Subtract 1 since the board index starts at 0.
      coordinate = tempCoordinates; // Set the temp coordinates as the coordinates to return.
      break;
    }
  }

  return coordinate;
}

bool GameBoard::maybePlaceBoat(const std::string &boatName, int boatLength, const BoatStart &boatPosition, bool printErrors) {
  std::vector<Coordinate> boatPositions = getBoatPositions(boatLength, boatPosition);

  if (!isValidPosition(boatPositions, printErrors)) {
    return false;
  }

  placeBoatOnBoard(boatName, boatPositions);

  return true;
}

void GameBoard::resetGameBoard() {
  std::cout << "Resetting game board...\n" << std::endl;
  gameBoard = ::createEmptyBoard(); // Reset the game board with an empty one.
  boatLocations.clear(); // Delete all stored boat locations.
}

/** Updates the board if hit and returns the type of hit. */
HitStatus GameBoard::getHitStatus(const Coordinate& maybeHitPosition) {
  std::string index = ::getBoardIndex(gameBoard, maybeHitPosition);

  if (index == ::EMPTY_STATE){
    return MISS;
  }

  std::string boatName = updateAndGetBoatHit(maybeHitPosition);
  if (boatName.empty()) {
    return MISS;
  }

  setHitStateOnBoard(maybeHitPosition); // Update the board since there was a hit.

  if (shipSunk(boatName)) { // If the ship was sunk.
    if (gameWon()) { // Check if this was the final ship to sink.
      return WIN; // If all boats are destroyed, return a HitStatus#WIN.
    }

    return SUNK; // Return a HitStatus#SUNK.
  }

  return HIT; // Return a HitStatus#HIT, but the boat was not sunk.
}

/** Sets the hit state on the board and updates the boat locations. */
void GameBoard::setHitStateOnBoard(const Coordinate& hitPosition) {
  ::setBoardIndexWithString(gameBoard, hitPosition, HIT_STATE); // Set the board position to the hit state.
}

/**
 * Deletes the section of the boat hit from the boatLocations map.
 * @returns the name of the boat hit, or else {@code ""}.
 */
std::string GameBoard::updateAndGetBoatHit(const Coordinate &hitPosition) {
  std::vector<std::string> boatNames = configSingleton.getBoatNames();
  for (auto &boatName : boatNames) { // Loop though every boat on the board till we find the one at this index.
    std::vector<Coordinate> boatCoordinates = boatLocations.find(boatName)->second;
    for (int i = 0; i < boatCoordinates.size(); i++) { // Loop though every position taken by this boat.
      Coordinate coordinate = boatCoordinates[i];
      if (coordinate.x == hitPosition.x && coordinate.y == hitPosition.y) { // If this position is the position that was hit.
        boatCoordinates.erase(boatCoordinates.begin() + i); // Remove this section of the boat.
        boatLocations.find(boatName)->second = boatCoordinates; // Update the boat locations.
        // Since the boat locations have been updated, return to avoid unneeded loops.
        return boatName; // Return the name of the boat.
      }
    }
  }

  return ""; // Return an empty string
}

/** Checks if there are any surviving boats on the board and returns true if not. */
bool GameBoard::gameWon() {
  for (auto const& boats : boatLocations) { // Loop though every boat in the map.
    if (!boats.second.empty()) { // Check if any boat still has sections remaining.
      return false; // If a section to a boat was found, return false as the game is not over.
    }
  }

  return true; // If all boats have no more locations, the game as been won.
}

bool GameBoard::shipSunk(const std::string& boatName) {
  std::vector<Coordinate> boatCoordinates = boatLocations.find(boatName)->second;
  if (boatCoordinates.empty()) {
    return true;
  }

  return false;
}

void GameBoard::initRandom() {
  rng = std::mt19937(rd()); // Initialise the random number generator, seeded with rd().
  randomBoolean = std::uniform_int_distribution<>(0, 1); // Used to generate a random boolean.
  // Minus 1 since uniform_int_distribution is closed range (ranges are inclusive).
  randomHeight = std::uniform_int_distribution<>(0, boardHeight - 1); // Used to generate a random int between 0 and the board height.
  randomWidth = std::uniform_int_distribution<>(0, boardWidth - 1); // Used to generate a random int between 0 and the board width.
}

std::vector<Coordinate> GameBoard::getBoatPositions(int boatLength, const BoatStart &boatStart) {
  std::vector<Coordinate> boatPositions; // Stores every index that this boat occupies.

  // Find the positions that the boat will take on the board, depending on the orientation.
  switch (boatStart.orientation) {
  case HORIZONTAL:
    for (int i = 0; i < boatLength; i++) {
      Coordinate coordinate;
      int number = ::getNumberFromAsciiLabel(boatStart.coordinate.x) + i;
      coordinate.x = ::getAsciiLabel(number);
      coordinate.y = boatStart.coordinate.y;
      boatPositions.push_back(coordinate); // Add the coordinates to the boat positions.
    }
    break;
  case VERTICAL:
    for (int i = 0; i < boatLength; i++) {
      Coordinate coordinate;
      coordinate.x = boatStart.coordinate.x;
      coordinate.y = boatStart.coordinate.y + i;
      boatPositions.push_back(coordinate); // Add the coordinates to the boat positions.
    }
    break;
  }

  return boatPositions;
}

bool GameBoard::isValidPosition(const std::vector<Coordinate> &boatPositions, bool printErrors) {
  // Check that each index that the boat will occupy is valid.
  for (const Coordinate& coordinate : boatPositions) {
    int xCoordinate = ::getNumberFromAsciiLabel(coordinate.x);
    int yCoordinate = coordinate.y;

    if (!isValidCoordinate(coordinate)) {
      if (printErrors) {
        std::cout << "Position " << ::getAsciiLabel(xCoordinate) << (yCoordinate + 1) << " is outside of the board, the boat must be placed within the board." << std::endl;
      }
      return false;
    }

    std::string index = ::getBoardIndex(gameBoard, coordinate);
    // Check if a boat already exists at this index.
    if (index != EMPTY_STATE){
      if (printErrors) {
        std::cout << "A boat already exists at " << ::getAsciiLabel(xCoordinate) << (yCoordinate + 1) << "." << std::endl;
      }
      return false;
    }
  }

  return true;
}

/** Check if this coordinate is outside of the board. */
bool GameBoard::isValidCoordinate(const Coordinate& coordinate) const {
  int xCoordinate = ::getNumberFromAsciiLabel(coordinate.x);
  int yCoordinate = coordinate.y;

  if (xCoordinate < 0 || xCoordinate > boardWidth || yCoordinate < 0 || yCoordinate > boardHeight) {
    return false;
  }

  return true;
}

void GameBoard::placeBoatOnBoard(const std::string &boatName, const std::vector<Coordinate> &boatPositions) {
  // Add this boat to the board.
  for (const Coordinate& coordinate : boatPositions) {
    ::setBoardIndexWithString(gameBoard, coordinate, {boatName[0]}); // Use the first letter of the boat name as its label.
  }

  // Add the board to the boat locations map.
  boatLocations.insert(std::pair<std::string, std::vector<Coordinate>>(boatName, boatPositions));
}

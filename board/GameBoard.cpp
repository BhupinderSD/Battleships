//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#include "GameBoard.h"
#include <cmath>

GameBoard::GameBoard() {
  gameBoard = createEmptyGameBoard(boardWidth, boardHeight);
}

void GameBoard::showBoard() {
  int width = boardWidth;
  int height = boardHeight;

  // Calculate the max length of an index on the board, so that each index can
  // be padded to the same length and the board can be evenly spaced.
  int maxWidthLength = getAsciiLabel(width - 1).length();
  int maxHeightLength = std::to_string(height).length();
  int maxIndexLength = std::max(maxWidthLength, maxHeightLength) + PADDING;

  // Start from -1 to account for the coordinate labels.
  for (int y = -1; y < height; y++) {
    for (int x = -1; x < width; x++) {
      std::string indexString;
      if (x == -1 && y == -1) { // Top left corner.
        indexString = ""; // Show an empty index.
      } else if (y == -1) { // Top row, for the coordinate labels.
        indexString = getAsciiLabel(x); // Use letters to represent the columns.
      } else if (x == -1) { // Left column, for the coordinate labels.
        indexString = std::to_string(y+1); // Use numbers to represent rows.
      } else { // Game board.
        indexString = gameBoard[x][y]; // Show the current game board index.
      }
      std::cout << padString(indexString, maxIndexLength);
    }
    std::cout << std::endl;
  }
}

bool GameBoard::maybePlaceBoat(const std::string& boatName, int boatLength, const BoatStart &boatPosition) {
  std::vector<Coordinate> boatPositions = getBoatPositions(boatLength, boatPosition);

  if (!isValidPosition(boatPositions)) {
    return false;
  }

  placeBoatOnBoard(boatName, boatPositions);

  return true;
}

std::vector<std::vector<std::string>> GameBoard::createEmptyGameBoard(int boardWidth, int boardHeight) {
  std::vector<std::vector<std::string>> gameBoard;

  for (int x = 0; x < boardWidth; x++) {
    std::vector<std::string> row; // Create a vector to represent this row.
    row.reserve(boardHeight); // Pre-allocate the capacity used by the for loop.
    for (int y = 0; y < boardHeight; y++) {
      row.emplace_back("[]"); // Add an empty board state to this index.
    }
    gameBoard.push_back(row); // Add this row to the game board.
  }

  return gameBoard;
}

std::vector<Coordinate> GameBoard::getBoatPositions(int boatLength, const BoatStart &boatStart) {
  std::vector<Coordinate> boatPositions; // Stores every index that this boat occupies.

  // Find the positions that the boat will take on the board, depending on the orientation.
  switch (boatStart.orientation) {
  case HORIZONTAL:
    for (int i = 0; i < boatLength; i++) {
      Coordinate coordinate;
      int number = getNumberFromAsciiLabel(boatStart.coordinate.x) + i;
      coordinate.x = getAsciiLabel(number);
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

bool GameBoard::isValidPosition(const std::vector<Coordinate>& boatPositions) {
  // Check that each index that the boat will occupy is valid.
  for (const Coordinate& coordinate : boatPositions) {
    int xCoordinate = getNumberFromAsciiLabel(coordinate.x);
    int yCoordinate = coordinate.y;
    // Check if any index of the boat extends the board.
    if (xCoordinate < 0 || xCoordinate >= boardWidth || yCoordinate < 0 || yCoordinate >= boardHeight) {
      std::cout << "Position " << getAsciiLabel(xCoordinate) << (yCoordinate + 1) << " is outside of the board, the boat must be placed within the board." << std::endl;
      return false;
    }

    std::string index = gameBoard[xCoordinate][yCoordinate];
    // Check if a boat already exists at this index.
    if (index != "[]"){
      std::cout << "A boat already exists at " << getAsciiLabel(xCoordinate) << (yCoordinate + 1) << "." << std::endl;
      return false;
    }
  }

  return true;
}

void GameBoard::placeBoatOnBoard(const std::string &boatName,
                                 const std::vector<Coordinate> &boatPositions) {
  // Add this boat to the board.
  for (const Coordinate& coordinate : boatPositions) {
    int xCoordinate = getNumberFromAsciiLabel(coordinate.x);
    gameBoard[xCoordinate][coordinate.y] = boatName[0];
  }

  // Add the board to the boat locations map.
  boatLocations.insert(std::pair<std::string, std::vector<Coordinate>>(boatName, boatPositions));
}

std::string GameBoard::getAsciiLabel(int number) {
  std::string string;

  while (number >= 0) {
    string = (char)('A' + number % 26 ) + string; // Get the right-most letter and place it in the string.
    number = number / 26; // Right shift to get the next letter.
    number--;
  }

  return string;
}

int GameBoard::getNumberFromAsciiLabel(const std::string& label) {
  int number = 0;

  for (int i = 0; i < label.size(); i++) {
    char character = label[label.size() - i - 1]; // Start from the end.
    character = std::toupper(character); // Ensure that the input is in upper case.
    // Converts the character to 1-26 and multiplies it to its place value.
    number += (character - 'A' + 1) * pow(26, i);
  }

  return number - 1;
}

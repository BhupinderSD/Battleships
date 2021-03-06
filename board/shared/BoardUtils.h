//
// Created by Bhupinder Dhoofer on 14/03/2021.
//

#include <cmath>
#include <utility>

static const std::string EMPTY_STATE = "[]";
static const std::string HIT_STATE = "*";
static const std::string MINE_STATE = "M";

const int PADDING = 2; // Padding so each index can be bigger than the max index length.

struct Coordinate { // A struct that stores the coordinates for a boat.
  std::string x;
  int y = 0;

  // Allows us to check if coordinates are equal.
  bool operator == (const Coordinate& coordinate) const {
    return coordinate.x == this->x && coordinate.y == this->y;
  }

  // Allows us to check if a coordinates are not equal.
  bool operator != (const Coordinate& coordinate) const {
    return coordinate.x != this->x || coordinate.y != this->y;
  }
};

enum HitStatus {
  HIT,
  SUNK,
  MISS,
  WIN,
  MINE
};

ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();
int boardWidth = configSingleton.getWidth();
int boardHeight = configSingleton.getHeight();

/** Converts a number to its alphabetical equivalent. The number 1 returns "A". */
std::string getAsciiLabel(int number) {
  std::string string;

  while (number >= 0) {
    string = (char)('A' + number % 26 ) + string; // Get the right-most letter and place it in the string.
    number = number / 26; // Right shift to get the next letter.
    number--;
  }

  return string;
}

/** Converts a Ascii label from {@link #getAsciiLabel} to its respective number. */
int getNumberFromAsciiLabel(const std::string& label) {
  int number = 0;

  for (int i = 0; i < label.size(); i++) {
    char character = label[label.size() - i - 1]; // Start from the end.
    character = std::toupper(character); // Ensure that the input is in upper case.
    // Converts the character to 1-26 and multiplies it to its place value.
    number += (character - 'A' + 1) * pow(26, i);
  }

  return number - 1;
}

/** Returns an {@link EMPTY_STATE} 2D vector of the required dimensions from
 * {@link ConfigurationSingleton}. */
std::vector<std::vector<std::string>> createEmptyBoard() {
  std::vector<std::vector<std::string>> board;

  for (int x = 0; x < boardWidth; x++) {
    std::vector<std::string> row; // Create a vector to represent this row.
    row.reserve(boardHeight); // Pre-allocate the capacity used by the for loop.
    for (int y = 0; y < boardHeight; y++) {
      row.emplace_back(EMPTY_STATE); // Add an empty board state to this index.
    }
    board.push_back(row); // Add this row to the board.
  }

  return board;
}

/** Displays the board contents with the board axes. */
void showBoard(std::vector<std::vector<std::string>> board) {
  // Calculate the max length of an index on the board, so that each index can
  // be padded to the same length and the board can be evenly spaced.
  int maxWidthLength = getAsciiLabel(boardWidth - 1).length();
  int maxHeightLength = std::to_string(boardHeight).length();
  int maxIndexLength = std::max(maxWidthLength, maxHeightLength) + PADDING;

  // Start from -1 to account for the coordinate labels.
  for (int y = -1; y < boardHeight; y++) {
    for (int x = -1; x < boardWidth; x++) {
      std::string indexString;
      if (x == -1 && y == -1) { // Top left corner.
        indexString = ""; // Show an empty index.
      } else if (y == -1) { // Top row, for the coordinate labels.
        indexString = getAsciiLabel(x); // Use letters to represent the columns.
      } else if (x == -1) { // Left column, for the coordinate labels.
        indexString = std::to_string(y+1); // Use numbers to represent rows.
      } else { // Board contents.
        indexString = board[x][y]; // Show the current board index.
      }
      std::cout << padString(indexString, maxIndexLength);
    }
    std::cout << std::endl;
  }
}

/** Returns the string stored at this coordinate. */
std::string getBoardIndex(std::vector<std::vector<std::string>> board, const Coordinate& coordinate) {
  int xCoordinate = getNumberFromAsciiLabel(coordinate.x); // Convert the Ascii coordinate to a column on the board.
  int yCoordinate = coordinate.y;

  return board[xCoordinate][yCoordinate];
}

/** Set the string at the coordinates on the board (by reference). */
void setBoardIndexWithString(std::vector<std::vector<std::string>> &board, const Coordinate& coordinate, std::string string) {
  int xCoordinate = getNumberFromAsciiLabel(coordinate.x); // Convert the Ascii coordinate to a column on the board.
  board[xCoordinate][coordinate.y] = std::move(string);
}

/**
 * Check if this coordinate is outside of the board. Here, height starts from
 * 1.
 */
bool isValidCoordinate(const Coordinate& coordinate) {
  int xCoordinate = ::getNumberFromAsciiLabel(coordinate.x);
  int yCoordinate = coordinate.y;

  if (xCoordinate < 0 || xCoordinate >= boardWidth || yCoordinate < 0 || yCoordinate > boardHeight) {
    return false;
  }

  return true;
}

/**
 * Check if this coordinate is outside of the board. Here, the height starts
 * from 0.
 */
bool isValidIndex(const Coordinate& coordinate) {
  int xCoordinate = ::getNumberFromAsciiLabel(coordinate.x);
  int yCoordinate = coordinate.y;

  if (xCoordinate < 0 || xCoordinate >= boardWidth || yCoordinate < 0 || yCoordinate >= boardHeight) {
    return false;
  }

  return true;
}

/** Sets the hit state for this and the immediately surrounding positions. */
void setMineHit(std::vector<std::vector<std::string>> &board, const Coordinate &hitPosition, const std::string& string) {
  int hitPositionXCoordinate = getNumberFromAsciiLabel(hitPosition.x);

  for (int i = -1; i < 2; i++) { // Loop though the immediately surrounding indices.
    for (int j = -1; j < 2; j++) {
      Coordinate mineHitCoordinate;
      mineHitCoordinate.x = ::getAsciiLabel(hitPositionXCoordinate + i);
      mineHitCoordinate.y = hitPosition.y + j;
      if (isValidIndex(mineHitCoordinate)) {
        ::setBoardIndexWithString(board, mineHitCoordinate, string); // Set the board position to the hit state.
      }
    }
  }
}
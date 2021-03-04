//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#ifndef BATTLESHIPS_BOARD_GAMEBOARD_H_
#define BATTLESHIPS_BOARD_GAMEBOARD_H_

enum Orientation { // An enum to identify the different orientations of a boat.
  HORIZONTAL,
  VERTICAL
};

struct Coordinate { // A struct that stores the coordinates for a boat.
  std::string x;
  int y = 0;
};

struct BoatStart { // A struct that stores the position and orientation for a boat.
  Coordinate coordinate;
  Orientation orientation;
};

struct BoatLocation {
  std::string boatName;
  std::vector<Coordinate> boatPositions;
};

class GameBoard {

  const int PADDING = 2; // Padding so each index can be bigger than the max index length.

  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();
  int boardWidth = configSingleton.getWidth();
  int boardHeight = configSingleton.getHeight();

  std::vector<std::vector<std::string>> gameBoard; // Use a 2D vector to represent the game board.

public:
  GameBoard(); // Constructor.

  void showBoard();

  static bool placeBoat(const std::string& boatName, int boatLength,
                        const BoatStart & boatPosition);

private:
  static std::vector<std::vector<std::string>> createEmptyGameBoard(int boardWidth, int boardHeight);

  static std::string getAsciiLabel(int number);

  static int getNumberFromAsciiLabel(const std::string& label);
};

#endif // BATTLESHIPS_BOARD_GAMEBOARD_H_

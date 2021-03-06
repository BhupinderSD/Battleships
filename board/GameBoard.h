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

class GameBoard {

  const int PADDING = 2; // Padding so each index can be bigger than the max index length.

  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();
  int boardWidth = configSingleton.getWidth();
  int boardHeight = configSingleton.getHeight();

  std::vector<std::vector<std::string>> gameBoard; // Use a 2D vector to represent the game board.

  std::map<std::string, std::vector<Coordinate>> boatLocations;

public:
  GameBoard(); // Constructor.

  void showBoard();

  void showPlacedAndUnplacedBoats();

  bool maybePlaceBoat(const std::string& boatName, int boatLength, const BoatStart & boatPosition);

  void resetGameBoard();

private:
  static std::vector<std::vector<std::string>> createEmptyGameBoard(int boardWidth, int boardHeight);

  static std::vector<Coordinate> getBoatPositions(int boatLength, const BoatStart & boatStart);

  bool isValidPosition(const std::vector<Coordinate>& boatPositions);

  void placeBoatOnBoard(const std::string& boatName, const std::vector<Coordinate>& boatPositions);

  static std::string getAsciiLabel(int number);

  static int getNumberFromAsciiLabel(const std::string& label);
};

#endif // BATTLESHIPS_BOARD_GAMEBOARD_H_

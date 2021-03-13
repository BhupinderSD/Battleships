//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#ifndef BATTLESHIPS_BOARD_GAMEBOARD_H_
#define BATTLESHIPS_BOARD_GAMEBOARD_H_

#include <random>

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

static const std::string EMPTY_STATE = "[]";
static const std::string HIT_STATE = "✸";

class GameBoard {

public:
  GameBoard(); // Constructor.

  void showBoard();

  void showPlacedAndUnplacedBoats();

  void autoPlaceUnplacedBoats();

  void setBoatOnBoard(const std::string& boatName, int boatLength);

  bool hasUnplacedBoats();

  void resetGameBoard();

  bool isHit(const Coordinate& maybeHitPosition);

private:

  const int PADDING = 2; // Padding so each index can be bigger than the max index length.

  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();
  int boardWidth = configSingleton.getWidth();
  int boardHeight = configSingleton.getHeight();

  std::vector<std::vector<std::string>> gameBoard; // Use a 2D vector to represent the game board.

  std::map<std::string, std::vector<Coordinate>> boatLocations;

  std::random_device rd;  // Used as the seed for the random number engine.
  std::mt19937 rng; // Random number generator seeded with rd().
  std::uniform_int_distribution<> randomBoolean; // Used to generate a random boolean.
  std::uniform_int_distribution<> randomHeight; // Used to generate a random int between 0 and the board height.
  std::uniform_int_distribution<> randomWidth; // Used to generate a random int between 0 and the board width.

  void initRandom();

  static std::vector<std::vector<std::string>> createEmptyGameBoard(int boardWidth, int boardHeight);

  static std::vector<Coordinate> getBoatPositions(int boatLength, const BoatStart & boatStart);

  bool isValidPosition(const std::vector<Coordinate> &boatPositions, bool printErrors);

  void placeBoatOnBoard(const std::string& boatName, const std::vector<Coordinate>& boatPositions);

  void setBoardIndexWithString(const Coordinate& coordinate, std::string string);

  void removeBoatFromBoardIfPlaced(const std::string& boatName);

  static Orientation getOrientation(const std::string& boatName);

  static Coordinate getCoordinates(const std::string& boatName);

  bool maybePlaceBoat(const std::string &boatName, int boatLength,const BoatStart &boatPosition, bool printErrors);

  void setHitState(const Coordinate& hitPosition);

  static std::string getAsciiLabel(int number);

  static int getNumberFromAsciiLabel(const std::string& label);
};

#endif // BATTLESHIPS_BOARD_GAMEBOARD_H_

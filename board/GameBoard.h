//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#ifndef BATTLESHIPS_BOARD_GAMEBOARD_H_
#define BATTLESHIPS_BOARD_GAMEBOARD_H_

#include "shared/BoardUtils.h"
#include "../HelperFunctions.h"
#include <random>
#include <cmath>

enum Orientation { // An enum to identify the different orientations of a boat.
  HORIZONTAL,
  VERTICAL
};

struct BoatStart { // A struct that stores the position and orientation for a boat.
  Coordinate coordinate;
  Orientation orientation;
};

class GameBoard {

public:
  GameBoard(); // Constructor.

  void showBoard();

  void showPlacedAndUnplacedBoats();

  void autoPlaceUnplacedBoats();

  Coordinate getRandomCoordinates();

  void setBoatOnBoard(const std::string& boatName, int boatLength);

  bool hasUnplacedBoats();

  void resetGameBoard();

  Coordinate getCoordinates(const std::string& boatName);

  HitStatus getHitStatus(const Coordinate& maybeHitPosition);

  int getSurvivingBoatCount();

private:

  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();
  int boardWidth = configSingleton.getWidth();
  int boardHeight = configSingleton.getHeight();

  std::string HIT_STATE = "✸";

  std::vector<std::vector<std::string>> gameBoard; // Use a 2D vector to represent the game board.

  std::map<std::string, std::vector<Coordinate>> boatLocations;

  std::random_device rd;  // Used as the seed for the random number engine.
  std::mt19937 rng; // Random number generator seeded with rd().
  std::uniform_int_distribution<> randomBoolean; // Used to generate a random boolean.
  std::uniform_int_distribution<> randomHeight; // Used to generate a random int between 0 and the board height.
  std::uniform_int_distribution<> randomWidth; // Used to generate a random int between 0 and the board width.

  void initRandom();

  static std::vector<Coordinate> getBoatPositions(int boatLength, const BoatStart & boatStart);

  bool isValidPosition(const std::vector<Coordinate> &boatPositions, bool printErrors);

  bool isValidCoordinate(const Coordinate& coordinate) const;

  bool isValidIndex(const Coordinate& coordinate) const;

  void placeBoatOnBoard(const std::string& boatName, const std::vector<Coordinate>& boatPositions);

  void removeBoatFromBoardIfPlaced(const std::string& boatName);

  static Orientation getOrientation(const std::string& boatName);

  bool maybePlaceBoat(const std::string &boatName, int boatLength,const BoatStart &boatPosition, bool printErrors);

  void setHitStateOnBoard(const Coordinate& hitPosition);

  std::string updateAndGetBoatHit(const Coordinate& hitPosition);

  bool gameWon();

  bool shipSunk(const std::string& boatName);
};

#endif // BATTLESHIPS_BOARD_GAMEBOARD_H_

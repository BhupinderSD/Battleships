//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_HUMANPLAYER_H_
#define BATTLESHIPS_PLAYER_HUMANPLAYER_H_

class HumanPlayer {

  enum Orientation { // An enum to identify the different orientations of a boat.
    LANDSCAPE,
    PORTRAIT
  };

  struct Coordinate { // A struct that stores the coordinates for a boat.
    std::string x;
    int y = 0;
  };

  struct BoatPosition { // A struct that stores the position and orientation for a boat.
    Coordinate coordinate;
    Orientation orientation;
  };

  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();
  std::map<std::string, int> boatsMap = configSingleton.getBoats();

  GameBoard gameBoard;

private:
  static Orientation getOrientation(const std::string& boatName);

  static Coordinate getCoordinates(const std::string& boatName);

public:
  HumanPlayer();

  void setBoatsOnBoard();
};

#endif // BATTLESHIPS_PLAYER_HUMANPLAYER_H_

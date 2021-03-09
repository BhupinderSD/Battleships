//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_HUMANPLAYER_H_
#define BATTLESHIPS_PLAYER_HUMANPLAYER_H_

class HumanPlayer {

  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();

  GameBoard gameBoard;

public:
  HumanPlayer();

  void setBoatsOnBoard();

private:
  void selectAndSetBoatsOnBoard();

  void setBoatOnBoard(const std::string& boatName, int boatLength);

  static Orientation getOrientation(const std::string& boatName);

  static Coordinate getCoordinates(const std::string& boatName);
};

#endif // BATTLESHIPS_PLAYER_HUMANPLAYER_H_

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

  Coordinate nextTurn();

  void updateIfHit(const Coordinate& torpedoLocation);

private:
  void selectAndSetBoatsOnBoard();

};

#endif // BATTLESHIPS_PLAYER_HUMANPLAYER_H_

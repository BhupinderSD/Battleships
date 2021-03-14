//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_HUMANPLAYER_H_
#define BATTLESHIPS_PLAYER_HUMANPLAYER_H_

class HumanPlayer {

public:
  HumanPlayer();

  void setBoatsOnBoard();

  Coordinate nextTurn();

  void updateIfHit(const Coordinate& torpedoLocation);

private:
  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();

  GameBoard gameBoard;
  HitBoard hitBoard;

  void selectAndSetBoatsOnBoard();

};

#endif // BATTLESHIPS_PLAYER_HUMANPLAYER_H_

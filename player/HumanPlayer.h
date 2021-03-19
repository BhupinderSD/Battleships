//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_HUMANPLAYER_H_
#define BATTLESHIPS_PLAYER_HUMANPLAYER_H_

#include "shared/PlayerUtils.h"

class HumanPlayer {

public:
  HumanPlayer();

  void setBoatsOnBoard();

  Coordinate nextTurn();

  HitStatus getHitStatus(const Coordinate& torpedoLocation);

  void updateHitBoard(const Coordinate& torpedoLocation, HitStatus hitStatus);

protected:
  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();

  GameBoard gameBoard;
  HitBoard hitBoard;

  void selectAndSetBoatsOnBoard();

  Coordinate getFireLocation();

};

#endif // BATTLESHIPS_PLAYER_HUMANPLAYER_H_

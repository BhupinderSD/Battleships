//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_HUMANPLAYER_H_
#define BATTLESHIPS_PLAYER_HUMANPLAYER_H_

#include "shared/Player.h"
#include "shared/PlayerUtils.h"

class HumanPlayer : public Player  {

public:
  HumanPlayer();

  void setBoatsOnBoard();

  Coordinate nextTurn() override;

  HitStatus getHitStatus(const Coordinate& torpedoLocation) override;

  void updateHitBoard(const Coordinate& torpedoLocation, HitStatus hitStatus) override;

protected:
  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();

  GameBoard gameBoard;
  HitBoard hitBoard;

  void selectAndSetBoatsOnBoard();

  Coordinate getFireLocation();

};

#endif // BATTLESHIPS_PLAYER_HUMANPLAYER_H_

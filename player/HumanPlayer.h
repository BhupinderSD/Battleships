//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_HUMANPLAYER_H_
#define BATTLESHIPS_PLAYER_HUMANPLAYER_H_

#include "shared/Player.h"
#include "shared/PlayerUtils.h"
#include "../HelperFunctions.h"

class HumanPlayer : public Player  {

public:
  explicit HumanPlayer(const std::string &playerName);

  Coordinate nextTurn() override;

  HitStatus getHitStatus(const Coordinate& torpedoLocation) override;

  void updateHitBoard(const Coordinate& torpedoLocation, HitStatus hitStatus) override;

  void waitToEndTurn() override;

protected:
  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();

  GameBoard gameBoard;
  HitBoard hitBoard;

  void placeBoats();

  void selectAndSetBoatsOnBoard();

  Coordinate getFireLocation();

};

#endif // BATTLESHIPS_PLAYER_HUMANPLAYER_H_

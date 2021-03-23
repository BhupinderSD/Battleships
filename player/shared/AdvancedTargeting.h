//
// Created by Bhupinder Dhoofer on 23/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_SHARED_ADVANCEDTARGETING_H_
#define BATTLESHIPS_PLAYER_SHARED_ADVANCEDTARGETING_H_

#include "PlayerUtils.h"

class AdvancedTargeting {

public:
  /**
  * Fires at random locations until a boat is hit. Once we have hit a boat and
  * while it has not sunk, we traverse every valid surrounding coordinate till it
  * has sunk.
  */
  Coordinate getFireLocation(GameBoard &gameBoard, HitBoard &hitBoard, std::string &playerName);

  void saveHit(const Coordinate &hitLocation, HitStatus hitStatus);

private:
  std::vector<Coordinate> locationsToSearch;

  void savePotentialLocations(const Coordinate &hitLocation);

};

#endif // BATTLESHIPS_PLAYER_SHARED_ADVANCEDTARGETING_H_

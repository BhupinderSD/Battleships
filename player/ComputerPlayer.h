//
// Created by Bhupinder Dhoofer on 12/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_COMPUTERPLAYER_H_
#define BATTLESHIPS_PLAYER_COMPUTERPLAYER_H_

#include "shared/AdvancedTargeting.cpp"
#include "shared/Player.h"
#include "shared/PlayerUtils.h"
#include "../HelperFunctions.h"

class ComputerPlayer : public Player {

public:
  explicit ComputerPlayer(const std::string &playerName);

  Coordinate nextTurn() override;

  HitStatus getHitStatus(const Coordinate& torpedoLocation) override;

  void updateHitBoard(const Coordinate& torpedoLocation, HitStatus hitStatus) override;

  void waitToEndTurn() override;

private:
  AdvancedTargeting advancedTargeting;
  bool askedAboutAdvancedTargeting = false;
  bool useAdvancedTargeting = false;

  void placeBoats();

  Coordinate getFireLocation();

  bool shouldUseAdvancedTargeting();

};

#endif // BATTLESHIPS_PLAYER_COMPUTERPLAYER_H_

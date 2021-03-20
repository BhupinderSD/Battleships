//
// Created by Bhupinder Dhoofer on 20/03/2021.
//

#include "Player.h"

bool Player::playNextTurnThenWin(Player &otherPlayer) {
  Coordinate humanTorpedoLocation = this->nextTurn();
  HitStatus humanHitStatus = otherPlayer.getHitStatus(humanTorpedoLocation);
  this->updateHitBoard(humanTorpedoLocation, humanHitStatus);
  if (humanHitStatus == WIN) {
    ::waitForUser("Press enter to end the game.\n");
    return true;
  } else {
    this->waitToEndTurn();
    return false;
  }
}

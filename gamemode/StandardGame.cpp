//
// Created by Bhupinder Dhoofer on 21/03/2021.
//

#include "StandardGame.h"

/** Returns true if the player plays the next turn then wins. */
bool StandardGame::playNextTurnThenWin(Player &player, Player &otherPlayer) {
  Coordinate humanTorpedoLocation = player.nextTurn();
  HitStatus humanHitStatus = otherPlayer.getHitStatus(humanTorpedoLocation);
  player.updateHitBoard(humanTorpedoLocation, humanHitStatus);
  if (humanHitStatus == WIN) {
    ::waitForUser("Press enter to end the game.\n");
    return true;
  } else {
    player.waitToEndTurn();
    return false;
  }
}

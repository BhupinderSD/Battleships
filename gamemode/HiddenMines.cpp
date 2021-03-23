//
// Created by Bhupinder Dhoofer on 21/03/2021.
//

#include "HiddenMines.h"

/** Returns true if the player plays the next turn then wins or quits. */
bool HiddenMines::playNextTurnAndMaybeFinish(Player &player, Player &otherPlayer) {
  Coordinate playerTorpedoLocation = player.nextTurn();
  HitStatus playerHitStatus = otherPlayer.getHitStatus(playerTorpedoLocation);
  player.updateHitBoard(playerTorpedoLocation, playerHitStatus);
  if (playerHitStatus == WIN) {
    player.waitToEndGame();
    return true;
  } else if (player.maybeQuitGame()) {
    return true;
  } else {
    player.waitToEndTurn();
    return false;
  }
}

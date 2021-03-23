//
// Created by Bhupinder Dhoofer on 21/03/2021.
//

#include "SalvoGame.h"

/** Returns true if the player plays the next turn then wins or quits. */
bool SalvoGame::playNextTurnAndMaybeFinish(Player &player, Player &otherPlayer) {
  int playerTurns = player.getGameBoard().getSurvivingBoatCount();

  while (playerTurns > 0) {
    playerTurns--;
    Coordinate playerTorpedoLocation = player.nextTurn();
    HitStatus playerHitStatus =
        otherPlayer.getHitStatus(playerTorpedoLocation);
    player.updateHitBoard(playerTorpedoLocation, playerHitStatus);
    if (playerHitStatus == WIN) {
      player.waitToEndGame();
      return true;
    } else if (player.maybeQuitGame()) {
      return true;
    } else {
      player.waitToEndTurn();
    }
  }

  return false;
}

//
// Created by Bhupinder Dhoofer on 21/03/2021.
//

#ifndef BATTLESHIPS_GAMEMODE_GAMEMODE_H_
#define BATTLESHIPS_GAMEMODE_GAMEMODE_H_

#include "../../player/shared/Player.h"

/** An abstract GameMode class with methods that all subclasses must implement. */
class GameMode {

public:
  /** Returns true if the player plays the next turn then wins or quits. */
  virtual bool playNextTurnAndMaybeFinish(Player &player, Player &otherPlayer) = 0;

};

#endif // BATTLESHIPS_GAMEMODE_GAMEMODE_H_

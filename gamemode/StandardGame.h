//
// Created by Bhupinder Dhoofer on 21/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_GAMEMODE_STANDARD_H_
#define BATTLESHIPS_PLAYER_GAMEMODE_STANDARD_H_

#include "shared/GameMode.h"
#include "../player/shared/Player.h"

class StandardGame : public GameMode {

private:
  bool playNextTurnThenWin(Player &player, Player &otherPlayer) override;

};

#endif // BATTLESHIPS_PLAYER_GAMEMODE_STANDARD_H_

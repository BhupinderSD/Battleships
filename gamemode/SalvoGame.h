//
// Created by Bhupinder Dhoofer on 21/03/2021.
//

#ifndef BATTLESHIPS_GAMEMODE_SALVOGAME_H_
#define BATTLESHIPS_GAMEMODE_SALVOGAME_H_

#include "shared/GameMode.h"

class SalvoGame : public GameMode {

private:
  bool playNextTurnThenWin(Player &player, Player &otherPlayer) override;

};

#endif // BATTLESHIPS_GAMEMODE_SALVOGAME_H_

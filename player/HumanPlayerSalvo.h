//
// Created by Bhupinder Dhoofer on 19/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_HUMANPLAYERSALVO_H_
#define BATTLESHIPS_PLAYER_HUMANPLAYERSALVO_H_

#include "HumanPlayer.h"

class HumanPlayerSalvo : public HumanPlayer {

public:
  explicit HumanPlayerSalvo(const std::string &playerName) : HumanPlayer(playerName) {};

  int getSurvivingBoatCount();

};

#endif // BATTLESHIPS_PLAYER_HUMANPLAYERSALVO_H_

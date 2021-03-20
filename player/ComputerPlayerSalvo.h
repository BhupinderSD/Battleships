//
// Created by Bhupinder Dhoofer on 19/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_COMPUTERPLAYERSALVO_H_
#define BATTLESHIPS_PLAYER_COMPUTERPLAYERSALVO_H_

#include "ComputerPlayer.h"

class ComputerPlayerSalvo : public ComputerPlayer {

public:
  explicit ComputerPlayerSalvo(const std::string &playerName) : ComputerPlayer(playerName) {};

  int getSurvivingBoatCount();

};

#endif // BATTLESHIPS_PLAYER_COMPUTERPLAYERSALVO_H_

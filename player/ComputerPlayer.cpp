//
// Created by Bhupinder Dhoofer on 12/03/2021.
//

#include "ComputerPlayer.h"

ComputerPlayer::ComputerPlayer() {
  gameBoard.autoPlaceUnplacedBoats();
  gameBoard.showBoard();
}


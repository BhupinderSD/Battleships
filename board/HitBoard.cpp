//
// Created by Bhupinder Dhoofer on 13/03/2021.
//

#include "HitBoard.h"

HitBoard::HitBoard() {
  hitBoard = ::createEmptyBoard();
}

void HitBoard::showBoard() {
  std::cout << "Hit board." << std::endl;
  ::showBoard(hitBoard);
}

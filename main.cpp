//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include "config/ConfigurationSingleton.cpp"
#include "board/GameBoard.cpp"
#include "player/HumanPlayer.cpp"

int main() {
  HumanPlayer humanPlayer;
  humanPlayer.setBoatsOnBoard();
}
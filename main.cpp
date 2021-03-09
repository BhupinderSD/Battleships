//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include "config/ConfigurationSingleton.cpp"
#include "board/GameBoard.cpp"
#include "player/HumanPlayer.cpp"

void playerVsComputer() {
  HumanPlayer humanPlayer;
  humanPlayer.setBoatsOnBoard();
}

void showMenu() {
  while (true) { // Ask the user to enter a game mode until they choose to quit.
    int option = getNumber("Please select a game mode: \n1. Player v Computer \n0. Reset", 0, 1);
    switch(option) {
    case 1:
      playerVsComputer();
      continue;
    case 0:
      std::cout << "Thanks for playing!" << std::endl;
      return;
    default:
      std::cout << "Invalid option, please try again." << std::endl;
      continue;
    }
  }
}

int main() {
  showMenu();
}
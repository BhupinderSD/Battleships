//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include "config/ConfigurationSingleton.cpp"
#include "board/GameBoard.cpp"
#include "board/HitBoard.cpp"
#include "player/HumanPlayer.cpp"
#include "player/ComputerPlayer.cpp"

void playerVsComputer() {
  std::cout << "Human Player." << std::endl;
  HumanPlayer humanPlayer;
  humanPlayer.setBoatsOnBoard();

  std::cout << "Computer Player." << std::endl;
  ComputerPlayer computerPlayer;

  while (true) {
    std::cout << "Human Player." << std::endl;
    Coordinate humanTorpedoLocation = humanPlayer.nextTurn();
    HitStatus humanHitStatus = computerPlayer.getHitStatus(humanTorpedoLocation);
    humanPlayer.updateHitBoard(humanTorpedoLocation, humanHitStatus);
    ::waitForUser("Press enter to end your turn.\n");

    std::cout << "Computer Player." << std::endl;
    Coordinate computerTorpedoLocation = computerPlayer.nextTurn();
    HitStatus computerHitStatus = humanPlayer.getHitStatus(computerTorpedoLocation);
    computerPlayer.updateHitBoard(computerTorpedoLocation, computerHitStatus);
    ::waitForUser("Press enter to end the computer's turn.\n");

    break; //TODO(Bhupinder): Keep looping till all boats for a player have been destroyed.
  }
}

void showMenu() {
  while (true) { // Ask the user to enter a game mode until they choose to quit.
    int option = getNumber("Please select a game mode: \n1. Player v Computer \n0. Quit", 0, 1);
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
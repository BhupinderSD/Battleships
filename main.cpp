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
    if (humanHitStatus == WIN) {
      ::waitForUser("Press enter to end the game.\n");
      break;
    } else {
      ::waitForUser("Press enter to end your turn.\n");
    }

    std::cout << "Computer Player." << std::endl;
    Coordinate computerTorpedoLocation = computerPlayer.nextTurn();
    HitStatus computerHitStatus = humanPlayer.getHitStatus(computerTorpedoLocation);
    computerPlayer.updateHitBoard(computerTorpedoLocation, computerHitStatus);
    if (computerHitStatus == WIN) {
      ::waitForUser("Press enter to end the game.\n");
      break;
    } else {
      ::waitForUser("Press enter to end the computer's turn.\n");
    }
  }
}

void playerVsPlayer() {
  std::cout << "Human Player 1." << std::endl;
  HumanPlayer humanPlayer1;
  humanPlayer1.setBoatsOnBoard();

  std::cout << "Human Player 2." << std::endl;
  HumanPlayer humanPlayer2;
  humanPlayer2.setBoatsOnBoard();

  while (true) {
    std::cout << "Human Player 1." << std::endl;
    Coordinate human1TorpedoLocation = humanPlayer1.nextTurn();
    HitStatus human1HitStatus = humanPlayer2.getHitStatus(human1TorpedoLocation);
    humanPlayer1.updateHitBoard(human1TorpedoLocation, human1HitStatus);
    if (human1HitStatus == WIN) {
      ::waitForUser("Press enter to end the game.\n");
      break;
    } else {
      ::waitForUser("Press enter to end your turn.\n");
    }

    std::cout << "Human Player 2." << std::endl;
    Coordinate human2TorpedoLocation = humanPlayer2.nextTurn();
    HitStatus human2HitStatus = humanPlayer1.getHitStatus(human2TorpedoLocation);
    humanPlayer2.updateHitBoard(human2TorpedoLocation, human2HitStatus);
    if (human2HitStatus == WIN) {
      ::waitForUser("Press enter to end the game.\n");
      break;
    } else {
      ::waitForUser("Press enter to end your turn.\n");
    }
  }
}

void showMenu() {
  while (true) { // Ask the user to enter a game mode until they choose to quit.
    int option = getNumber("Please select a game mode: \n1. Player v Computer\n2. Player v Player \n0. Quit", 0, 2);
    switch(option) {
    case 1:
      playerVsComputer();
      continue;
    case 2:
      playerVsPlayer();
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
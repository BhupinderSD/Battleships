//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include "config/ConfigurationSingleton.cpp"
#include "board/GameBoard.cpp"
#include "board/HitBoard.cpp"
#include "player/shared/Player.h"
#include "player/HumanPlayer.cpp"
#include "player/HumanPlayerSalvo.cpp"
#include "player/ComputerPlayer.cpp"
#include "player/ComputerPlayerSalvo.cpp"

void playStandardGame(Player &player1, Player &player2) {
  while (true) {
    Coordinate humanTorpedoLocation = player1.nextTurn();
    HitStatus humanHitStatus = player2.getHitStatus(humanTorpedoLocation);
    player1.updateHitBoard(humanTorpedoLocation, humanHitStatus);
    if (humanHitStatus == WIN) {
      ::waitForUser("Press enter to end the game.\n");
      break;
    } else {
      player1.waitToEndTurn();
    }

    Coordinate computerTorpedoLocation = player2.nextTurn();
    HitStatus computerHitStatus = player1.getHitStatus(computerTorpedoLocation);
    player2.updateHitBoard(computerTorpedoLocation, computerHitStatus);
    if (computerHitStatus == WIN) {
      ::waitForUser("Press enter to end the game.\n");
      break;
    } else {
      player2.waitToEndTurn();
    }
  }
}

void playerVsComputer() {
  HumanPlayer humanPlayer("Human Player");
  ComputerPlayer computerPlayer("Computer Player");

  playStandardGame(humanPlayer, computerPlayer);
}

void playerVsPlayer() {
  HumanPlayer humanPlayer1("Human Player 1");
  HumanPlayer humanPlayer2("Human Player 2");

  playStandardGame(humanPlayer1, humanPlayer2);
}

void playerVsComputerSalvo() {
  HumanPlayerSalvo humanPlayer("Human Player");
  ComputerPlayerSalvo computerPlayer("Computer Player");

  while (true) {
    int humanTurns = humanPlayer.getSurvivingBoatCount();
    while (humanTurns > 0) {
      humanTurns--;
      Coordinate humanTorpedoLocation = humanPlayer.nextTurn();
      HitStatus humanHitStatus =
          computerPlayer.getHitStatus(humanTorpedoLocation);
      humanPlayer.updateHitBoard(humanTorpedoLocation, humanHitStatus);
      if (humanHitStatus == WIN) {
        ::waitForUser("Press enter to end the game.\n");
        return;
      }
    }
    humanPlayer.waitToEndTurn();

    int computerTurns = computerPlayer.getSurvivingBoatCount();
    while (computerTurns > 0) {
      computerTurns--;
      Coordinate computerTorpedoLocation = computerPlayer.nextTurn();
      HitStatus computerHitStatus =
          humanPlayer.getHitStatus(computerTorpedoLocation);
      computerPlayer.updateHitBoard(computerTorpedoLocation, computerHitStatus);
      if (computerHitStatus == WIN) {
        ::waitForUser("Press enter to end the game.\n");
        return;
      }
    }
    computerPlayer.waitToEndTurn();
  }
}

void playerVsPlayerSalvo() {
  HumanPlayerSalvo humanPlayer1("Human Player 1");
  HumanPlayerSalvo humanPlayer2("Human Player 2");

  while (true) {
    int human1Turns = humanPlayer1.getSurvivingBoatCount();
    while (human1Turns > 0) {
      human1Turns--;
      Coordinate human1TorpedoLocation = humanPlayer1.nextTurn();
      HitStatus human1HitStatus =
          humanPlayer2.getHitStatus(human1TorpedoLocation);
      humanPlayer1.updateHitBoard(human1TorpedoLocation, human1HitStatus);
      if (human1HitStatus == WIN) {
        ::waitForUser("Press enter to end the game.\n");
        return;
      }
    }
    humanPlayer1.waitToEndTurn();

    int human2Turns = humanPlayer2.getSurvivingBoatCount();
    while (human2Turns > 0) {
      human2Turns--;
      Coordinate human2TorpedoLocation = humanPlayer2.nextTurn();
      HitStatus human2HitStatus =
          humanPlayer1.getHitStatus(human2TorpedoLocation);
      humanPlayer2.updateHitBoard(human2TorpedoLocation, human2HitStatus);
      if (human2HitStatus == WIN) {
        ::waitForUser("Press enter to end the game.\n");
        return;
      }
    }
    humanPlayer2.waitToEndTurn();
  }
}

void showMenu() {
  while (true) { // Ask the user to enter a game mode until they choose to quit.
    int option = getNumber("Please select a game mode: \n1. Player v Computer\n2. Player v Player\n3. Player v Computer (salvo)\n4. Player v Player (salvo)\n0. Quit", 0, 4);
    switch(option) {
    case 1:
      playerVsComputer();
      continue;
    case 2:
      playerVsPlayer();
      continue;
    case 3:
      playerVsComputerSalvo();
      continue;
    case 4:
      playerVsPlayerSalvo();
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
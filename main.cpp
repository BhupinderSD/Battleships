//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include "config/ConfigurationSingleton.cpp"
#include "board/GameBoard.cpp"
#include "board/HitBoard.cpp"
#include "player/shared/Player.h"
#include "player/HumanPlayer.cpp"
#include "player/ComputerPlayer.cpp"
#include "gamemode/shared/GameMode.h"
#include "gamemode/StandardGame.cpp"
#include "gamemode/SalvoGame.cpp"
#include "gamemode/HiddenMines.cpp"

/** Plays the battleship game with a {@code gameMode} until a player wins. */
void playGame(Player &player1, Player &player2, GameMode &gameMode) {
  while (true) {
    if (gameMode.playNextTurnAndMaybeFinish(player1, player2)) {
      break;
    }

    if (gameMode.playNextTurnAndMaybeFinish(player2, player1)) {
      break;
    }
  }
}

void playerVsComputerStandard() {
  HumanPlayer humanPlayer("Human Player");
  ComputerPlayer computerPlayer("Computer Player");
  StandardGame standardGame;

  playGame(humanPlayer, computerPlayer, standardGame);
}

void playerVsPlayerStandard() {
  HumanPlayer humanPlayer1("Human Player 1");
  HumanPlayer humanPlayer2("Human Player 2");
  StandardGame standardGame;

  playGame(humanPlayer1, humanPlayer2, standardGame);
}

void playerVsComputerSalvo() {
  HumanPlayer humanPlayer("Human Player");
  ComputerPlayer computerPlayer("Computer Player");
  SalvoGame salvoGame;

  playGame(humanPlayer, computerPlayer, salvoGame);
}

void playerVsPlayerSalvo() {
  HumanPlayer humanPlayer1("Human Player 1");
  HumanPlayer humanPlayer2("Human Player 2");
  SalvoGame salvoGame;

  playGame(humanPlayer1, humanPlayer2, salvoGame);
}

/** Enables hidden mines for both plays and prints a message informing the user. */
void setHiddenMines(Player &player1, Player &player2) {
  player1.getGameBoard().setHiddenMines();
  player2.getGameBoard().setHiddenMines();
  std::cout << "Mines have been placed!\n" << std::endl;
}

void playerVsComputerHiddenMines() {
  HumanPlayer humanPlayer("Human Player");
  ComputerPlayer computerPlayer("Computer Player");
  HiddenMines hiddenMines;

  setHiddenMines(humanPlayer, computerPlayer);

  playGame(humanPlayer, computerPlayer, hiddenMines);
}

void playerVsPlayerHiddenMines() {
  HumanPlayer humanPlayer1("Human Player 1");
  HumanPlayer humanPlayer2("Human Player 2");
  HiddenMines hiddenMines;

  setHiddenMines(humanPlayer1, humanPlayer2);

  playGame(humanPlayer1, humanPlayer2, hiddenMines);
}

void ComputerVsComputerHiddenMines() {
  ComputerPlayer computerPlayer1("Computer Player 1");
  ComputerPlayer computerPlayer2("Computer Player 2");
  HiddenMines hiddenMines;

  setHiddenMines(computerPlayer1, computerPlayer2);

  playGame(computerPlayer1, computerPlayer2, hiddenMines);
}

void showMenu() {
  while (true) { // Ask the user to enter a game mode until they choose to quit.
    int option = getNumber("Please select a game mode: \n"
                           "1. Player v Computer\n"
                           "2. Player v Player\n"
                           "3. Player v Computer (salvo)\n"
                           "4. Player v Player (salvo)\n"
                           "5. Player v Computer (hidden mines)\n"
                           "6. Player v Player (hidden mines)\n"
                           "7. Computer v Computer (hidden mines)\n"
                           "0. Quit", 0, 7);
    switch(option) {
    case 1:
      playerVsComputerStandard();
      continue;
    case 2:
      playerVsPlayerStandard();
      continue;
    case 3:
      playerVsComputerSalvo();
      continue;
    case 4:
      playerVsPlayerSalvo();
      continue;
    case 5:
      playerVsComputerHiddenMines();
      continue;
    case 6:
      playerVsPlayerHiddenMines();
      continue;
    case 7:
      ComputerVsComputerHiddenMines();
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
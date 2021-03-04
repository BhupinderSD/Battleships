//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include "config/ConfigurationSingleton.cpp"
#include "board/GameBoard.cpp"
#include "player/HumanPlayer.cpp"

int main() {
  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();
  int width = configSingleton.getWidth();
  int height = configSingleton.getHeight();
  std::map<std::string, int> boatsMap = configSingleton.getBoats();

  GameBoard gameBoard(width, height);
  gameBoard.showBoard();

  HumanPlayer humanPlayer;
  humanPlayer.setBoats(boatsMap);
}
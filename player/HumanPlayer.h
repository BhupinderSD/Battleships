//
// Created by Bhupinder Dhoofer on 03/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_HUMANPLAYER_H_
#define BATTLESHIPS_PLAYER_HUMANPLAYER_H_

class HumanPlayer {

public:
  HumanPlayer();

  void setBoatsOnBoard();

  Coordinate nextTurn();

  bool updateIfHit(const Coordinate& torpedoLocation);

  void updateHitBoard(const Coordinate& torpedoLocation, bool hitStatus);

private:
  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();

  GameBoard gameBoard;
  HitBoard hitBoard;

  void selectAndSetBoatsOnBoard();

};

#endif // BATTLESHIPS_PLAYER_HUMANPLAYER_H_

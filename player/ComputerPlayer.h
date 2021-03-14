//
// Created by Bhupinder Dhoofer on 12/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_COMPUTERPLAYER_H_
#define BATTLESHIPS_PLAYER_COMPUTERPLAYER_H_

class ComputerPlayer {

public:
  ComputerPlayer();

  Coordinate nextTurn();

  bool updateIfHit(const Coordinate& torpedoLocation);

  void updateHitBoard(const Coordinate& torpedoLocation, bool hitStatus);

private:
  GameBoard gameBoard;
  HitBoard hitBoard;

};

#endif // BATTLESHIPS_PLAYER_COMPUTERPLAYER_H_

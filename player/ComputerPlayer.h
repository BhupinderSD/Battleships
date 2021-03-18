//
// Created by Bhupinder Dhoofer on 12/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_COMPUTERPLAYER_H_
#define BATTLESHIPS_PLAYER_COMPUTERPLAYER_H_

class ComputerPlayer {

public:
  ComputerPlayer();

  Coordinate nextTurn();

  HitStatus getHitStatus(const Coordinate& torpedoLocation);

  void updateHitBoard(const Coordinate& torpedoLocation, HitStatus hitStatus);

private:
  GameBoard gameBoard;
  HitBoard hitBoard;

  void placeBoats();

  Coordinate getFireLocation();

};

#endif // BATTLESHIPS_PLAYER_COMPUTERPLAYER_H_

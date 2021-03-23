//
// Created by Bhupinder Dhoofer on 23/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_SHARED_ADVANCEDTARGETING_H_
#define BATTLESHIPS_PLAYER_SHARED_ADVANCEDTARGETING_H_

class AdvancedTargeting {

public:
  Coordinate getFireLocation(GameBoard &gameBoard, HitBoard &hitBoard, std::string &playerName);

  void saveHit(const Coordinate &hitLocation, HitStatus hitStatus);

private:
  std::map<Coordinate, HitStatus> fireLocations;

};

#endif // BATTLESHIPS_PLAYER_SHARED_ADVANCEDTARGETING_H_

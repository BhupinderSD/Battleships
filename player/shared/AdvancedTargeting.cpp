//
// Created by Bhupinder Dhoofer on 23/03/2021.
//

#include "AdvancedTargeting.h"

void AdvancedTargeting::saveHit(const Coordinate &hitLocation, HitStatus hitStatus) {
  fireLocations.insert(std::pair<Coordinate, HitStatus>(hitLocation, hitStatus));
}

Coordinate AdvancedTargeting::getFireLocation(GameBoard &gameBoard, HitBoard &hitBoard, std::string &playerName) {
  // TODO(Bhupinder): Implement advanced firing
  return ::getAutoFireLocation(gameBoard, hitBoard, playerName);
}

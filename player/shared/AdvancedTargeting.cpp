//
// Created by Bhupinder Dhoofer on 23/03/2021.
//

#include "AdvancedTargeting.h"

// TODO(Bhupinder): Implement advanced firing
Coordinate AdvancedTargeting::getFireLocation(GameBoard &gameBoard, HitBoard &hitBoard, std::string &playerName) {
  if (locationsToSearch.empty()) {
    return ::getAutoFireLocation(gameBoard, hitBoard, playerName);
  }

  return ::getAutoFireLocation(gameBoard, hitBoard, playerName);
}

void AdvancedTargeting::saveHit(const Coordinate &hitLocation, HitStatus hitStatus) {
  if (hitStatus == SUNK) { // Reset the current state since the boat we were looking for has sunk.
    locationsToSearch.clear();
  }

  if (hitStatus == HIT) { // Save the surrounding locations so we can start hunting for the rest of the boat.
    saveSurroundingLocations(hitLocation);
  }
}

void AdvancedTargeting::saveSurroundingLocations(const Coordinate&hitLocation) {
  int xCoordinate = getNumberFromAsciiLabel(hitLocation.x);
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      Coordinate coordinate;
      coordinate.x = ::getAsciiLabel(xCoordinate + i);
      coordinate.y = hitLocation.y + j;

      if (::isValidIndex(coordinate) && coordinate != hitLocation) {
        locationsToSearch.push_back(hitLocation);
      }
    }
  }
}

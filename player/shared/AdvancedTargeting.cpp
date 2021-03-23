//
// Created by Bhupinder Dhoofer on 23/03/2021.
//

#include "AdvancedTargeting.h"

/**
 * Fires at random locations until a boat is hit. Once we have hit a boat and
 * while it has not sunk, we traverse every valid surrounding coordinate till it
 * has sunk.
 */
Coordinate AdvancedTargeting::getFireLocation(GameBoard &gameBoard, HitBoard &hitBoard, std::string &playerName) {
  if (locationsToSearch.empty()) { // If we have no coordinates to search, fire at a random one.
    return ::getAutoFireLocation(gameBoard, hitBoard, playerName);
  }

  Coordinate coordinateToSearch = locationsToSearch[0]; // Get the next location to search in the vector.
  locationsToSearch.erase(locationsToSearch.begin()); // Remove the location that we are about to search.

  ::printFiringCoordinates(playerName, coordinateToSearch); // Prints the location this player is firing at.

  return coordinateToSearch;
}

void AdvancedTargeting::saveHit(const Coordinate &hitLocation, HitStatus hitStatus) {
  if (hitStatus == SUNK) { // Reset the current state since the boat we were looking for has sunk.
    locationsToSearch.clear();
  }

  if (hitStatus == HIT) { // Save the surrounding locations so we can start hunting for the rest of the boat.
    savePotentialLocations(hitLocation);
  }
}

void AdvancedTargeting::savePotentialLocations(const Coordinate &hitLocation) {
  int hitLocationXCoordinate = getNumberFromAsciiLabel(hitLocation.x);

  Coordinate left;
  left.x = ::getAsciiLabel(hitLocationXCoordinate - 1);
  left.y = hitLocation.y;
  Coordinate top;
  top.x = ::getAsciiLabel(hitLocationXCoordinate);
  top.y = hitLocation.y + 1;
  Coordinate right;
  right.x = ::getAsciiLabel(hitLocationXCoordinate + 1);
  right.y = hitLocation.y;
  Coordinate bottom;
  bottom.x = ::getAsciiLabel(hitLocationXCoordinate);
  bottom.y = hitLocation.y - 1;
  Coordinate potentialLocations[] = {left, top, right, bottom};

  for (const Coordinate& coordinate : potentialLocations) {
    if (::isValidIndex(coordinate)) {
      locationsToSearch.push_back(coordinate);
    }
  }
}

//
// Created by Bhupinder Dhoofer on 19/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_SHARED_PLAYERUTILS_H_
#define BATTLESHIPS_PLAYER_SHARED_PLAYERUTILS_H_

/** Prints out the coordinates, adjusted so the height starts at 1. */
void printCoordinate(Coordinate coordinate) {
  std::cout << coordinate.x << std::to_string(coordinate.y + 1) << std::endl;
}

/** Returns a random coordinate that hasn't been used on the hit board. */
Coordinate getAutoFireLocation(GameBoard &gameBoard, HitBoard hitBoard) {
  Coordinate fireTorpedoLocation;

  while (true) { // Keep generating coordinates till we receive a valid/unused location.
    fireTorpedoLocation = gameBoard.getRandomCoordinates();

    if (hitBoard.isValidLocation(fireTorpedoLocation)) {
      break;
    }
  }

  printCoordinate(fireTorpedoLocation);

  return fireTorpedoLocation;
}

#endif // BATTLESHIPS_PLAYER_SHARED_PLAYERUTILS_H_

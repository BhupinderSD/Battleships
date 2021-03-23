//
// Created by Bhupinder Dhoofer on 20/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_SHARED_PLAYER_H_
#define BATTLESHIPS_PLAYER_SHARED_PLAYER_H_

#include "../../HelperFunctions.h"

/** An abstract Player class with methods that all subclasses must implement. */
class Player {

protected:

  std::string playerName;

  GameBoard gameBoard;
  HitBoard hitBoard;

  explicit Player(const std::string& playerName) : hitBoard(playerName), gameBoard(playerName) {
    this->playerName = playerName;
  };

public:

  /** Returns the coordinates for the next turn from this player. */
  virtual Coordinate nextTurn() = 0;

  /**
   * Updates the game board for the player the if the {@code torpedoLocation}
   * from another player hit a boat and returns the type of hit (or miss).
   */
  virtual HitStatus getHitStatus(const Coordinate& torpedoLocation) = 0;

  /**
   * Updates the hit board for the player with the {@link HitStatus} from the
   * opponents {@link Player#getHitStatus}.
   */
  virtual void updateHitBoard(const Coordinate& torpedoLocation, HitStatus hitStatus) = 0;

  /** Displays a message informing the user to end the game, since they have won. */
  void waitToEndGame() {
    ::waitForUser(playerName + " - Press enter to end the game.\n");
  };

  /** Asks the user if they want to quit the game. Returns true if the game should end. */
  virtual bool maybeQuitGame() = 0;

  /** Displays a message informing the user to end the turn. */
  void waitToEndTurn() {
    ::waitForUser(playerName + " - Press enter to end this turn.\n");
  };

  /** Returns the gameboard. */
  GameBoard& getGameBoard() { return gameBoard; }

};

#endif // BATTLESHIPS_PLAYER_SHARED_PLAYER_H_

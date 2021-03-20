//
// Created by Bhupinder Dhoofer on 20/03/2021.
//

#ifndef BATTLESHIPS_PLAYER_SHARED_PLAYER_H_
#define BATTLESHIPS_PLAYER_SHARED_PLAYER_H_

/** An abstract Player class with methods that all subclasses must implement. */
class Player {

protected:

  std::string playerName;

  GameBoard gameBoard;
  HitBoard hitBoard;

  explicit Player(const std::string& playerName) {
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

  /** Displays a message informing the user to end the turn. */
  virtual void waitToEndTurn() = 0;

  /** Plays the next turn and returns true if the player wins on this turn. */
  bool playNextTurnThenWin(Player &otherPlayer);

};

#endif // BATTLESHIPS_PLAYER_SHARED_PLAYER_H_

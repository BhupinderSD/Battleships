
## AP 2 - Battleships

Repl link: https://replit.com/@BhupinderSD/Battleships

Repl invite link: https://replit.com/join/vijspmcj-bhupindersd


## Challenge outline


### Summary and proposed solution

The challenge that I have to complete is to design and create “AdaShip”, a clone of the classic battleships game. Battleships is a turn based strategy/guessing game. AdaShip is a command line variant of battleships. I will be expected to create multiple game modes along with player types, so efficient use of good programming skills and OOP will help with programming AdaShip.

There are a large number of requirements for all aspects of the challenge. Below are my initial thoughts and the proposed solution.


#### Configuration

The board size, boat names, length and count must all be customisable in an `adaship_config.ini` file. I think that this will be best implemented as a singleton class, since we only need to read the config data once at runtime and we can use the same data for the rest of the program's run time.


#### Board

The board must use a fixed coordinate notation, where the y axis is represented by numbers and the x axis is represented by the alphabet (and if the board is wider than 26 units, the alphabet must repeat again, so after Z is AA). So that the board is displayed correctly and evenly spaced, I will pad every cell in the board to the same width. I will need to create two boards, one to represent the game board and all the boats on it, and the second to represent the hit board and where the player has hit the other player in past turns.


#### Game modes and Menu

I will be implementing the following game modes:



*   Player v Computer
*   Player v Player
*   Player v Computer (salvo)
*   Player v Player (salvo)
*   Player v Computer (hidden mines)
*   Player v Player (hidden mines)
*   Computer v Computer (hidden mines)

I will present this menu from main and I plan to keep it very simple so that it is easy to add more game modes and player combinations.


#### Players

I will need to support two players, a human player and a computer player. In order to reuse code, and since both players will need to do the same things, I think that it will be best to use an abstract player class, which will be inherited by a human and computer class. This will let me reuse code since I can use the general players base class as a parameter to functions and methods and call the common virtual methods that both subclasses implement.


### UML diagram

[UML diagram](battleships.png?raw=true "UML diagram")


### Initial working plan

My overall approach to this project will be to complete everything to a high standard. I will write detailed commit messages and refactor my code whenever I think that something can be done better. I will also test new and existing features after every commit and I will also test my code on Repl frequently to ensure that it will still work. My development strategy will be to split the several components into their own directories and ensure that they can all work together. I will use the clion ide to help with debugging whenever required. As visible in my UML diagram above, multiple components communicate with each other. Ensuring that all components work together will be vital. I will add detailed comments as I go, so that I know what a method does and any implementation details as well.


### Analysis and decomposition

As shown in the UML diagram, proposed solution and explained above, the components for this challenge will be the epics.



*   Epic 1 - Parsing the configuration
*   Epic 2 - Player(s)
*   Epic 3 - Boards
*   Epic 4 - Game modes

I explain how I will break down these epics and why I chose them in the section below.


### Object orientated design ideas and phased breakdown

The epic numbers above is the general order in which I will create the program. Since I will not be using hardcoded configuration data, it makes sense to create a working configuration parser first. This will make it easier to create and test the game board and hit board. However, I will create a player before the boards so that I can try to place data on the board. Once the game and hit boards are working correctly, I can work on implementing the other game modes.

As explained in the proposed solution section above, the configuration parser will be a singleton class. I will only need to read the configuration data the first time I need it, and every time it is accessed after that, I can retrieve it from the same initial instance. This approach makes sense since I don’t expect or support the configuration data changing during runtime.

Using abstract classes for the players and game modes will allow me to reuse the same methods in main, which will display the game menu. This will help with readability and also reduce code duplication.

In order to test all the epics to a minimally viable solution, I will first implement a player vs player game with the standard game mode. This will let me test the game board and hit board logic. Once all edge cases and bugs are resolved, I can start implementing the rest of the game modes and the computer player.

There will be some code that can be shared between components and subclasses, so I will place these as helper functions in a shared directory. An example for this could be any printing logic and input selections.


## Development


### Use of good standards

Since C++ is a new language to me, I thought it would be best to use an ide such as clion. This will help me with minor mistakes that I make, auto imports and also small optimisations that I can make that I miss, such as making a parameter constant.

In order to help myself and other viewers of my code, I will try to make sure that everything is as readable as possible. I will add method comments explaining what a method is doing as well as implementation comments when something that I am doing could be confusing.

I will be following the KISS principle and will keep the code as simple as possible. Using abstract classes should help with this. Meaningful variable and method names will also be really important. I will also try to make sure that commits only do one thing. This will make it easy to find when something was implemented and if there are any bugs, it can be easier to find out which commit may have caused it.


### Development


#### Phase 1 - Parsing the configuration

The configuration file had to be in a specific format. The following are the default values.

```

Board: 10x10

Boat: Carrier, 5

Boat: Battleship, 4

Boat: Destroyer, 3

Boat: Submarine, 3

Boat: Patrol Boat, 2

```

As you can see, the board dimensions are set once but the key `boat` is used multiple times. For this reason, I chose to use a multimap<string, string>, where the key is either `Boat` or `Board` and the value is the text after `:`. I extracted a split method since I could reuse it to get the board dimensions, by splitting on `x`. I can also split by `,` in order to separate the boat name from the boat length.

```

/** Splits a string into a vector of strings, split by the specified delimiter. */

std::vector<std::string> split(const std::string &s, char delimiter) {

  std::vector<std::string> strings;

  std::stringstream sstream(s);

  std::string string;

  while(std::getline(sstream, string, delimiter)) {

    strings.push\_back(string);

  }

  return strings;

}

```

Once I have extracted all of the data from the config file to the multimap, I validate it by ensuring that the multimap contains the board dimensions and a boat. If it does not, I let the user know and use default values so the user can continue to play the game.

After validating the multimap, I extract the data into fields of the singleton that can be retrieved later.

```

void ConfigurationSingleton::setConfigurationData(const std::multimap<std::string, std::string>& configMultiMap) {

  for (auto &itr : configMultiMap) { // Iterate through every key and value in the MultiMap.

    if (itr.first == BOARD\_KEY) { // Check if the board dimensions have been set in the config file.

      setBoardDimensions(itr.second);

    } else if (itr.first == BOAT\_KEY) { // Check if any boats have been set in the config file.

      addToBoatsMap(itr.second);

    }

  }

}

```


#### Phase 2 - Players

Next, I created a HumanPlayer class. I created methods to ask the user for coordinates so that we can place boats (from the config singleton) on the board. For every boat to place, I ask for the orientation of the boat and then the starting coordinate for the boat. I also added validation and error handling for as many scenarios as I could think of.

Then, I continued to add more functionality to this class as well as the game board class. I also added support for moving placed boats and resetting the board. I then added support for auto placements, which I could then use for the Computer Player.


#### Phase 3 - Boards

I worked on this at the same time as Players, since I would need both for testing and development. I use the board dimensions from the configuration singleton to render the board. One of the bigger challenges was creating the x axis and also parsing it from the user entered coordinates.

```

    // Split the x and y coordinates.

    for (char character : userCoordinates) {

      if (isalpha(character)) {

        tempCoordinates.x += toupper(character);

      } else if (isdigit(character)) {

        tempCoordinates.y = tempCoordinates.y \* 10 + (character - '0');

      }

    }

```

I use this algorithm to split a userCoordinates string into the x and y coordinates. I then check if the user entered the coordinates in the required notation and if they are missing any data, such as an x coordinate, y coordinates or if the provided coordinates are invalid. If the coordinates are valid, I exit a `while (true)` loop (so I can keep asking till I get valid coordinates) and return the coordinates.

```

    // Check that the coordinates are valid.

    if (tempCoordinates.x.empty() && tempCoordinates.y == 0) {

      std::cout << "Please enter valid coordinates.\n" << std::endl;

    } else if (tempCoordinates.x.empty()) {

      std::cout << "Please enter a valid x coordinate (a letter).\n" << std::endl;

    } else if (tempCoordinates.y == 0) {

      std::cout << "Please enter a valid y coordinate (a number).\n" << std::endl;

    } else if (!::isValidCoordinate(tempCoordinates)) {

      std::cout << tempCoordinates.x << tempCoordinates.y << "Please enter valid coordinates within the bounds of the board.\n" << std::endl;

    } else {

      tempCoordinates.y = tempCoordinates.y - 1; // Subtract 1 since the board index starts at 0.

      coordinate = tempCoordinates; // Set the temp coordinates as the coordinates to return.

      break;

    }

```


### Bugs and testing


### Reflection


## Evaluation


### Analysis


### Features showcase and embedded innovations


### Improved targeting algorithm


### Reflective review

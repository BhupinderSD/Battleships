//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include "../HelperFunctions.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <sys/stat.h>
#include <vector>

#ifndef BATTLESHIPS_CONFIGURATIONSINGLETON_H
#define BATTLESHIPS_CONFIGURATIONSINGLETON_H

static std::string CONFIG_FILE = "adaship_config.ini"; // Name of the external data file.
static std::string BOARD_KEY = "Board"; // Key for the board dimensions in the config file.
static std::string BOAT_KEY = "Boat"; // Key for each boat in the config file.

class ConfigurationSingleton {

  int boardWidth = 10;  // Default width for the board.
  int boardHeight = 10;  // Default height for the board.
  std::map<std::string, int> boatMap; // A map containing the name and length for each boat.
  std::vector<std::string> boatNames; // A vector containing the name for each boat.

public:
  static ConfigurationSingleton& getInstance();

  ConfigurationSingleton(ConfigurationSingleton const&) = delete; // Singletons should not be cloneable.

  void operator = (ConfigurationSingleton const&) = delete; // Singletons should not be assignable.

  int getWidth() const;

  int getHeight() const;

  std::map<std::string, int> getBoatMap();

  std::vector<std::string> getBoatNames();

private:
  ConfigurationSingleton();

  static std::multimap<std::string, std::string> readConfigFileToMultiMap();

  static void verifyConfigurationData(std::multimap<std::string, std::string>& configMultiMap);

  void setConfigurationData(const std::multimap<std::string, std::string>& configMultiMap);

  void setBoardDimensions(const std::string& dimensions);

  void addToBoatsMap(const std::string& boatInfo);

  static std::vector<std::string> setBoatNames(const std::map<std::string, int>& boatMap);
};

#endif //BATTLESHIPS_CONFIGURATIONSINGLETON_H

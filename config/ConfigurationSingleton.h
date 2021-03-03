//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include "../HelperFunctions.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <sys/stat.h>
#include <vector>

#ifndef BATTLESHIPS_CONFIGURATIONSINGLETON_H
#define BATTLESHIPS_CONFIGURATIONSINGLETON_H

static std::string CONFIG_FILE = "adaship_config.ini"; // Name of the external data file.

class ConfigurationSingleton {

  // Using a MultiMap so we can store the same key with multiple values.
  std::multimap<std::string, std::string> configMultiMap{};

private:
  ConfigurationSingleton();

public:
  static ConfigurationSingleton& getInstance();

  ConfigurationSingleton(ConfigurationSingleton const&) = delete; // Singletons should not be cloneable.

  void operator = (ConfigurationSingleton const&) = delete; // Singletons should not be assignable.

  std::multimap<std::string, std::string> getConfigMultiMap();;
};

#endif //BATTLESHIPS_CONFIGURATIONSINGLETON_H

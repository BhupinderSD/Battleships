//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include "config/ConfigurationSingleton.cpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int main() {
  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();
  std::map<std::string, std::string> configMap = configSingleton.getConfigMap();

  int height = 10;  //default height
  int width = 10;  //default width

  if (configMap.find("Board") != configMap.end()) { // Check if the board dimensions have been set in the config file.
    std::vector<std::string> boardDimensions = split(configMap.find("Board")->second, 'x'); // Get the two numbers on either side of 'x'.
    // Update the width and height with the values from the config file.
    width = std::stoi(boardDimensions[0]);
    height = std::stoi(boardDimensions[1]);
  }
}
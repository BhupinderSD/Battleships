//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include "ConfigurationSingleton.h"
#include <algorithm>

ConfigurationSingleton &ConfigurationSingleton::getInstance() {
  static ConfigurationSingleton instance; // Instantiated on first use and guaranteed to be destroyed.
  return instance;
}

ConfigurationSingleton::ConfigurationSingleton() {  // Constructor.
  std::multimap<std::string, std::string> configMultiMap = readConfigFileToMultiMap();
  setConfigurationData(configMultiMap);
}

int ConfigurationSingleton::getWidth() const { return boardWidth; }

int ConfigurationSingleton::getHeight() const { return boardHeight; }

std::map<std::string, int> ConfigurationSingleton::getBoats() {
  return boatMap;
}

std::multimap<std::string, std::string> ConfigurationSingleton::readConfigFileToMultiMap() {
  // Using a MultiMap so we can store the same key with multiple values.
  std::multimap<std::string, std::string> configMultiMap;

  if (!fileExists(CONFIG_FILE)) { // Check if the file does not exist.
    std::cout << "Sorry, \'" << CONFIG_FILE << "\' does not exist." << std::endl;
    return configMultiMap;
  }

  std::string lineInFile;
  std::ifstream file; // Initialise an input stream.
  file.open(CONFIG_FILE); // Open the file to read it.

  while (!file.eof()) { // While we are not at the end of the file.
    getline(file, lineInFile); // Read the line in the file and save it in the variable lineInFile.
    lineInFile.erase(remove_if(lineInFile.begin(), lineInFile.end(), isspace), lineInFile.end()); // Remove spaces in the line.
    std::vector<std::string> iniSplit = split(lineInFile, ':');
    configMultiMap.insert(std::pair<std::string, std::string>(iniSplit[0], iniSplit[1]));
  }

  file.close(); // Close the file stream

  return configMultiMap;
}

void ConfigurationSingleton::setConfigurationData(
    const std::multimap<std::string, std::string>& configMultiMap) {
  for (auto &itr : configMultiMap) { // Iterate though every key and value in the MultiMap.
    if (itr. first == BOARD_KEY) { // Check if the board dimensions have been set in the config file.
      // Get the two numbers on either side of 'x'.
      std::vector<std::string> boardDimensions = split(itr. second, 'x');

      // Update the width and height with the values from the config file.
      boardWidth = std::stoi(boardDimensions[0]);
      boardHeight = std::stoi(boardDimensions[1]);
    } else if (itr. first == BOAT_KEY) { // Check if any boats have been set in the config file.
      // Get the boat name and length on either side of ','.
      std::vector<std::string> boats = split(itr. second, ',');

      std::string boatName = boats[0]; // Get the boat name as a string.
      int boatLength = std::stoi(boats[1]); // Get the boat length as an int.

      // Only add the boat to the map if it has a unique name.
      if (boatMap.find(boatName) == boatMap.end()) {
        boatMap.insert(std::pair<std::string, int>(boatName, boatLength));
      } else {
        std::cout << "Duplicated boat \'" << boatName << "\', each boat must be unique." << std::endl;
      }
    }
  }
}

//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include "ConfigurationSingleton.h"

ConfigurationSingleton &ConfigurationSingleton::getInstance() {
  static ConfigurationSingleton instance; // Instantiated on first use and guaranteed to be destroyed.
  return instance;
}

ConfigurationSingleton::ConfigurationSingleton() {  // Constructor.
  std::multimap<std::string, std::string> configMultiMap = readConfigFileToMultiMap();
  verifyConfigurationData(configMultiMap);
  setConfigurationData(configMultiMap);
  boatNames = setBoatNames(boatMap);
}

int ConfigurationSingleton::getWidth() const { return boardWidth; }

int ConfigurationSingleton::getHeight() const { return boardHeight; }

std::map<std::string, int> ConfigurationSingleton::getBoatMap() {
  return boatMap;
}

std::vector<std::string> ConfigurationSingleton::getBoatNames() {
  return boatNames;
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

void ConfigurationSingleton::verifyConfigurationData(std::multimap<std::string, std::string> &configMultiMap) {
  if (configMultiMap.find(BOARD_KEY) == configMultiMap.end()) {
    // Inform the user that the default board dimensions will be used.
    std::cout << "No board dimensions specified, using 10x10." << std::endl;
  }

  if (configMultiMap.find(BOAT_KEY) == configMultiMap.end()) {
    // Inform the user that a default single boat will be used.
    std::cout << "No boats specified, using a single boat." << std::endl;
    configMultiMap.insert(std::pair<std::string, std::string>(BOAT_KEY, "Carrier, 5"));
  }
}

void ConfigurationSingleton::setConfigurationData(const std::multimap<std::string, std::string>& configMultiMap) {
  for (auto &itr : configMultiMap) { // Iterate through every key and value in the MultiMap.
    if (itr.first == BOARD_KEY) { // Check if the board dimensions have been set in the config file.
      setBoardDimensions(itr.second);
    } else if (itr.first == BOAT_KEY) { // Check if any boats have been set in the config file.
      addToBoatsMap(itr.second);
    }
  }
}

void ConfigurationSingleton::setBoardDimensions(const std::string& dimensions) {
  // Get the two numbers on either side of 'x'.
  std::vector<std::string> boardDimensions = split(dimensions, 'x');

  try { // Try to set the dimensions from the config file.
    // Update the width and height with the values from the config file.
    boardWidth = std::stoi(boardDimensions[0]);
    boardHeight = std::stoi(boardDimensions[1]);
  } catch (...) { // If we fail to set the dimensions, we will use the default value 10x10.
    std::cout << "Unable to set board dimensions \'" << boardDimensions[0] << " x " << boardDimensions[1] << "\', ensure you are using the correct format in "<< CONFIG_FILE << ". Using 10x10." << std::endl;
  }

  // Ensure that the board dimensions are valid.
  if (boardWidth <= 0) {
    std::cout << "The board width must be more than 0, using default value 10." << std::endl;
    boardWidth = 10;
  }

  if (boardHeight <= 0) {
    std::cout << "The board height must be more than 0, using default value 10." << std::endl;
    boardHeight = 10;
  }
}

void ConfigurationSingleton::addToBoatsMap(const std::string &boatInfo) {
  // Get the boat name and length on either side of ','.
  std::vector<std::string> boats = split(boatInfo, ',');

  std::string boatName = "Boat"; // Default value for the boat name is 'Boat'.
  int boatLength = 4; // Default length for a boat is '4'.

  if (!boats[0].empty()) { // Only set the new name if it is not empty.
    boatName = boats[0]; // Get the boat name as a string.
  } else { // Inform the user that the default value will be used.
    std::cout << "The boat name cannot be empty, using default name Boat." << std::endl;
  }

  try {
    boatLength = std::stoi(boats[1]); // Get the boat length as an int.
  } catch (...) { // If we fail to set the board length, we the default value.
    std::cout << "Unable to set boat \'" << boatName << "\' of length  \'" << boats[1] << "\'. Ensure you are using the correct format in " << CONFIG_FILE << ". Using default length 4." << std::endl;
  }

  // Ensure that the boat length is valid.
  if (boatLength <= 0) {
    std::cout << "The boat length must be more than 0, using default value 4." << std::endl;
    boatLength = 4;
  }

  // Only add the boat to the map if it has a unique name.
  if (boatMap.find(boatName) == boatMap.end()) {
    boatMap.insert(std::pair<std::string, int>(boatName, boatLength));
  } else {
    std::cout << "Duplicated boat \'" << boatName << "\', each boat must be unique." << std::endl;
  }
}

std::vector<std::string> ConfigurationSingleton::setBoatNames(const std::map<std::string, int>& boatMap) {
  std::vector<std::string> boatNames;

  boatNames.reserve(boatMap.size()); // Pre-allocate the capacity used by the for loop.
  for (auto &itr : boatMap) { // Iterate though every boat in the map.
    boatNames.push_back(itr.first); // Add every boat name to the vector.
  }

  return boatNames;
}
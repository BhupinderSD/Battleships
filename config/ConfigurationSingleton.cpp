//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include "ConfigurationSingleton.h"

ConfigurationSingleton::ConfigurationSingleton() {  // Constructor.
  if (!fileExists(CONFIG_FILE)) { // Check if the file does not exist.
    std::cout << "Sorry, \'" << CONFIG_FILE << "\' does not exist.\n";
    return;
  }

  std::string lineInFile;
  std::ifstream file; // Initialise an input stream.
  file.open(CONFIG_FILE); // Open the file to read it.

  while (!file.eof()) { // While we are not at the end of the file.
    getline(file, lineInFile); // Read the line in the file and save it in the variable lineInFile.
    lineInFile.erase(remove_if(lineInFile.begin(), lineInFile.end(), isspace), lineInFile.end()); // Remove spaces in the line.
    std::vector<std::string> iniSplit = split(lineInFile, ':');
    configMap.insert(std::pair<std::string, std::string>(iniSplit[0], iniSplit[1]));
  }
  file.close(); // Close the file stream

}
ConfigurationSingleton &ConfigurationSingleton::getInstance() {
  static ConfigurationSingleton instance; // Instantiated on first use and guaranteed to be destroyed.
  return instance;
}

std::map<std::string, std::string> ConfigurationSingleton::getConfigMap() {
  return configMap;
}

//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include "config/ConfigurationSingleton.cpp"

int main() {
  ConfigurationSingleton& configSingleton = ConfigurationSingleton::getInstance();
  int width = configSingleton.getWidth();
  int height = configSingleton.getHeight();
  std::map<std::string, int> boats = configSingleton.getBoats();
}
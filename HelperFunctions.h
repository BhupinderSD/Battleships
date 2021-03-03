//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include <sstream>
#include <sys/stat.h>
#include <vector>

#ifndef BATTLESHIPS__HELPERFUNCTIONS_H_
#define BATTLESHIPS__HELPERFUNCTIONS_H_

/* Checks if a file with the specified filename exists. */
bool fileExists(const std::string& filename) {
  struct stat buffer{};
  bool fileExists = stat(filename.c_str(), &buffer) == 0; //check if the file exists
  return fileExists;
}

/* Splits a string into a vector of strings, split by the specified delimiter. */
std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> strings;
  std::stringstream sstream(s);
  std::string string;
  while(std::getline(sstream, string, delimiter)) {
    strings.push_back(string);
  }
  return strings;
}

/* Adds the same character to a string a specified number of times. */
std::string createStringOfChar(char character, int requiredLength) {
  std::string string = "";

  for (int i = 0; i < requiredLength; i++) {
    string += character; //append the character until we meet the required length
  }

  return string;
}

/* Pads the string with spaces till the required length. */
std::string padString(std::string string, int requiredLength) {
  int length = string.length();

  if (requiredLength > length) { // Check if we need to pad with more characters.
    int charsRequired = requiredLength - length;
    string += createStringOfChar(' ', charsRequired); // Append more spaces till the required length is met.
  }

  return string;
}

#endif // BATTLESHIPS__HELPERFUNCTIONS_H_

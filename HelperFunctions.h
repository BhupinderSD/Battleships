//
// Created by Bhupinder Dhoofer on 02/03/2021.
//

#include <codecvt>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <vector>

#ifndef BATTLESHIPS__HELPERFUNCTIONS_H_
#define BATTLESHIPS__HELPERFUNCTIONS_H_

/** Checks if a file with the specified filename exists. */
bool fileExists(const std::string& filename) {
  struct stat buffer{};
  bool fileExists = stat(filename.c_str(), &buffer) == 0; //check if the file exists
  return fileExists;
}

/** Splits a string into a vector of strings, split by the specified delimiter. */
std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> strings;
  std::stringstream sstream(s);
  std::string string;
  while(std::getline(sstream, string, delimiter)) {
    strings.push_back(string);
  }
  return strings;
}

/** Adds the same character to a string a specified number of times. */
std::string createStringOfChar(char character, int requiredLength) {
  std::string string = "";

  for (int i = 0; i < requiredLength; i++) {
    string += character; // Append the character until we meet the required length.
  }

  return string;
}

/** Returns the real length of a string, even if a char takes multiple bytes. */
std::size_t getCharCount(const std::string& string){
  return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t >{}.from_bytes(string).size();
}

/** Pads the string with spaces till the required length. */
std::string padString(std::string string, int requiredLength) {
  int length = getCharCount(string);

  if (requiredLength > length) { // Check if we need to pad with more characters.
    int charsRequired = requiredLength - length;
    string += createStringOfChar(' ', charsRequired); // Append more spaces till the required length is met.
  }

  return string;
}

/** Returns the user input after asking them the specified question. */
std::string getLine(std::string request) {
  std::string string;
  std::cout << request << std::endl;
  getline(std::cin, string);
  return string;
}

/** Clears the cin stream state and cin buffer. */
void flushBuffer() {
  std::cin.clear(); // Resets the cin stream state so that future I/O operations work correctly.
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // Clears the cin buffer including new lines or additional characters.
}

/** Get a number that is larger than or equal to startRange and smaller than or equal to endRange. */
int getNumber(std::string request, int startRange, int endRange) {
  int number;

  std::cout << request << std::endl;
  std::cin >> number;
  while(std::cin.fail() || number < startRange || number > endRange) { // While the user enters an invalid input, keep asking for a valid input.
    std::cout << "Invalid input.\n\n";
    flushBuffer();
    std::cout << request << std::endl;
    std::cin >> number;
  }
  flushBuffer();
  return number;
}

/** Print a list with the title and the strings in the vector. */
void printList(const std::string& title, const std::vector<std::string>& placedBoats) {
  if (!placedBoats.empty()) {
    std::cout << title << std::endl;
    for (const std::string& boatName : placedBoats) {
      std::cout << boatName << std::endl;
    }
    std::cout << std::endl;
  }
}

#endif // BATTLESHIPS__HELPERFUNCTIONS_H_

#include "filereader.h"

#include <fstream>
#include <iostream>
#include <algorithm>

std::vector<std::string> FileReader::readLines(std::string filename) {
  // result vector
  std::vector<std::string> result;

  // open file
  std::ifstream infile(filename);
  std::string line;
  while (std::getline(infile, line)) {
    // strip newline
    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
    result.push_back(line);
  }
  return result;
}

std::string FileReader::read(std::string filename) {
  return concat(readLines(filename));
}

std::string FileReader::concat(std::vector<std::string> lines) {
  // result string
  std::string result = "";
  for (std::string line : lines) {
    result += line;
  }
  return result;
}

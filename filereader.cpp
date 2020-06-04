/***
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

Copyright 2020, David Herzig (dave.herzig@gmail.com)
***/

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

std::string FileReader::readFasta(std::string filename) {
  return concat(readLines(filename), true);
}

std::string FileReader::concat(std::vector<std::string> lines, bool isFastaFormat) {
  char skipLineCharacters[] = {'>'};
  int numberOfSkipLineCharacter = 1;

  std::string result = "";
  for (std::string line : lines) {
    bool skipLine = false;
    if (isFastaFormat) {
      for (int i=0; i<numberOfSkipLineCharacter; i++) {
        if (line.find(skipLineCharacters[i]) == 0) {
          skipLine = true;
          break;
        }
      }
    }
    if (!skipLine) {
      result += line;
    }
  }
  return result;
}

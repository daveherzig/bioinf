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

#include "util.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

std::vector<bool> Util::getStartIndices(std::string sequence, int length) {
  std::vector<bool> coverage(sequence.size());

  int minOverlap = ceil(0.3 * length);
  int minAmount = sequence.size() / (length - minOverlap);

  // create random based substrings
  int counter = 0;
  while (counter < minAmount) {
    int startIndex = rand() % (sequence.size() - length + 1);
    if (coverage[startIndex]) {
      continue;
    }
    coverage[startIndex] = true;
    counter++;
  }

  // check if the first and last possible substring is covered
  coverage[0] = true;
  coverage[sequence.size()-length] = true;

  // verify if each position is covered
  int maxGap = length - minOverlap - 1;
  int lastCoveredStartPosition = -1;
  for (int i=0; i<sequence.size() - length + 1; i++) {
    if (!coverage[i]) {
      if ((i - lastCoveredStartPosition) > maxGap) {
        coverage[i] = true;
        lastCoveredStartPosition = i;
      }
    } else {
      lastCoveredStartPosition = i;
    }
  }

  return coverage;
}

std::vector<std::string> Util::splitSequence(std::string sequence, int length) {

  std::vector<std::string> result;
  std::vector<bool> coverage = getStartIndices(sequence, length);

  for (int i=0; i<coverage.size(); i++) {
    if (coverage[i]) {
      result.push_back(sequence.substr(i, length));
    }
  }

  return result;
}

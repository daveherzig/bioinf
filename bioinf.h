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

#ifndef BIOINF_H
#define BIOINF_H

#include <string>
#include <vector>
#include <map>

class BioInf {
private:
  /**
   * This method counts all possible words of length k in text.
   */
  static std::map<std::string, int> countWords(std::string text, int k);
public:
  static int patternCount(std::string text, std::string pattern);
  static std::vector<int> patternMatch(std::string text, std::string pattern);
  static std::vector<std::string> frequentWords(std::string text, int k);
  static std::string reverseComplement(std::string text);
  static std::vector<std::string> findClumps(std::string text, int k, int windowLength, int minOccurence);
  static std::vector<std::string> kmer(std::string text, int k);


  static void createDeBruijnGraph(std::vector<std::string> kmers);


};

#endif

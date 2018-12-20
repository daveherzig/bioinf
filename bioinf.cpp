#include "bioinf.h"

#include <algorithm>
#include <set>
#include <iostream>

std::vector<std::string> BioInf::findClumps(std::string text, int k, int windowLength, int minOccurence) {
  std::set<std::string> result;
  int loopRange = text.size()-windowLength+1;
  for (int i=0; i<loopRange; i++) {
    std::string window = text.substr(i, windowLength);
    std::map<std::string, int> resultMap = countWords(window, k);
    for (std::map<std::string, int>::iterator it=resultMap.begin(); it!=resultMap.end(); it++) {
      if (it->second >= minOccurence) {
        result.insert(it->first);
      }
    }
  }

  // convert set to vector
  std::vector<std::string> vResult;
  vResult.assign(result.begin(), result.end());
  return vResult;
}

int BioInf::patternCount(std::string text, std::string pattern) {
  return patternMatch(text, pattern).size();
}

std::vector<int> BioInf::patternMatch(std::string text, std::string pattern) {
  std::vector<int> result;
  int startindex = 0;
  int n = text.find(pattern, startindex);
  while (n >= 0) {
    result.push_back(n);
    startindex = n + 1;
    n = text.find(pattern, startindex);
  }
  return result;
}

std::map<std::string, int> BioInf::countWords(std::string text, int k) {
  std::map<std::string, int> result;

  for (int i=0; i<text.size()-k+1; i++) {
    std::string pattern = text.substr(i, k);
    if (result.find(pattern) == result.end()) {
      result[pattern] = 1;
    } else {
      result[pattern] = result[pattern]+1;
    }
  }
  return result;
}

std::vector<std::string> BioInf::frequentWords(std::string text, int k) {
  std::map<std::string, int> resultMap = countWords(text, k);

  // get the highest value from the map
  int maxValue = -1;
  for (std::map<std::string, int>::iterator it=resultMap.begin(); it!=resultMap.end(); it++) {
    if (it->second > maxValue) {
      maxValue = it->second;
    }
  }

  std::vector<std::string> result;
  for (std::map<std::string, int>::iterator it=resultMap.begin(); it!=resultMap.end(); it++) {
    if (it->second == maxValue) {
      result.push_back(it->first);
    }
  }

  return result;
}

std::string BioInf::reverseComplement(std::string text) {
  std::string result = text;
  std::reverse(result.begin(), result.end());

  std::map<char, char> mapping;
  mapping['A'] = 'T';
  mapping['T'] = 'A';
  mapping['G'] = 'C';
  mapping['C'] = 'G';

  for (int i=0; i<result.size(); i++) {
    char current = result[i];
    if (mapping.find(current) != mapping.end()) {
      result[i] = mapping[result[i]];
    }
  }

  return result;
}

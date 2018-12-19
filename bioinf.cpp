#include "bioinf.h"

#include <algorithm>
#include <map>
#include <iostream>

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

std::vector<std::string> BioInf::frequentWords(std::string text, int k) {
  std::map<std::string, int> resultMap;

  for (int i=0; i<text.size()-k+1; i++) {
    std::string pattern = text.substr(i, k);
    if (resultMap.find(pattern) == resultMap.end()) {
      resultMap[pattern] = 1;
    } else {
      resultMap[pattern] = resultMap[pattern]+1;
    }
  }

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

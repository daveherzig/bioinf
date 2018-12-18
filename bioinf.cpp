#include "bioinf.h"

#include <algorithm>
#include <map>
#include <iostream>

int BioInf::patternCount(std::string text, std::string pattern) {
  int result = 0;
  int startindex = 0;
  int n = text.find(pattern, startindex);
  while (n >= 0) {
    result++;
    startindex = n + 1;
    n = text.find(pattern, startindex);
  }
  return result;
}

std::vector<std::string> BioInf::frequentWords(std::string text, int k) {

  std::map<std::string, int> resultMap;

  for (int i=0; i<text.size()-k; i++) {
    std::string pattern = text.substr(i, k);
    if (resultMap.find(pattern) == resultMap.end()) {
      resultMap[pattern] = patternCount(text, pattern);
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

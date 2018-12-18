#include "bioinf.h"

#include <algorithm>

#include <iostream>
using namespace std;

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

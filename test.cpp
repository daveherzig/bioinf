#include "bioinf.h"
#include "filereader.h"

#include <iostream>
#include <map>
#include <cassert>
#include <chrono>
using namespace std;

class TimeUtil {
private:
  static std::map<std::string, double> results;
public:
  static void start();
};

/**
 * Test method for the pattern count method.
 */
void testPatternCount() {
  string t = "CTATTTGCTCTATTTGGTGCTATTTGCTATTTGTCCTATTTGCCTATTTGCTATTTGAACTATTTGCTATTTGCCTATTTGTCTATTTGCTATTTGCTATTTGCCTATTTGACTATTTGTCTATTTGACTATTTGTCCCTATTTGAACTATTTGGGTAACAGCTATTTGTCGTACTACCTATTTGCAGAGCCCTATTTGAACCCTATTTGCTATTTGAAACCAACTATTTGGTGTAATGTCTCTACTATTTGCTATTTGACTATTTGACCCTATTTGCTATTTGCGCTATTTGCTATTTGGTCTATTTGCTATTTGTCCTATTTGTATACTATTTGCTGCTATTTGACTATTTGCTCTTCTATTTGGACTGGGCTATTTGCTCTATTTGCTATTTGTTCCTATTTGCTATTTGCTCTATTTGTCTATTTGCTATTTGATCTATTTGCTATTTGGTTACTATTTGCGACTATTTGCTATTTGCCTATTTGCTATTTGAACTATTTGTGGGTGCTATTTGCTATTTGCTATTTGAACTATTTGCTATTTGTGGCCACTATTTGCGCTATTTGCCTATTTGCGCTATTTGCGGAGACTATTTGCTATTTGCTATTTGATGGCTATTTGCTATTTGCTATTTGTGATCTATTTGGGGTGCTTACCCTATTTGCTTTTGTTCCTATTTGGCTATTTGAATTACTGGTCCTATTTGCTATTTGTGCCTATTTGACGTGCTGCTATTTGCTATTTGCCTGGCTTCTATTTGCGCTATTTGTTGAGACTATTTGGGATAATCTATTTGAACGCTATTTGGTACTCCACCGGCCTATTTGCTGAGCTATTTGCTATTTGTTATGCTGTAATCTATTTGAACTATTTGGTCTATTTGACTATTTGTTCTATTTGTACACTATTTGTCTATTTGAAAACCCCTATTTGCGTCTATTTGCTATTTGCGAGGTCTATTTGCTATTTGTCCCTATTTGGCCTATTTGCTATTTGCTATTTGCTATTTGCTATTTGTCCACTATTTGGAACTATTTGCTATTTG";
  string p = "CTATTTGCT";

  int expectedValue = 40;
  int value = BioInf::patternCount(t, p);
  vector<int> indices = BioInf::patternMatch(t, p);

  assert(value == expectedValue);
  assert(indices.size() == expectedValue);
}

void testFrequentWords() {
  string t = "ACGTTGCATGTCGCATGATGCATGAGAGCT";
  vector<string> expectedValues;
  expectedValues.push_back("CATG");
  expectedValues.push_back("GCAT");
  int counter = 0;
  vector<string> values = BioInf::frequentWords(t, 4);
  for (string s : values) {
    counter++;
    assert(std::find(expectedValues.begin(), expectedValues.end(), s) != expectedValues.end());
  }

  assert(counter == expectedValues.size());
}

void testReverseComplement() {
  string sequence = "AAAACCCGGT";
  string value = BioInf::reverseComplement(sequence);
  string expectedValue = "ACCGGGTTTT";

  assert(value == expectedValue);
}

void performanceFrequentWords() {
  string sequence = FileReader::read("data/mm_ref_GRCm38.p4_chr1.fa");
  cout << "Sequence Length: " << sequence.size() << endl;
  auto start = std::chrono::system_clock::now();
  vector<string> values = BioInf::frequentWords(sequence, 10);
  auto stop = std::chrono::system_clock::now();
  for (string s : values) {
    cout << s << endl;
  }
}


int main(int argc, char **argv) {
  testPatternCount();
  testFrequentWords();
  testReverseComplement();

  //performanceFrequentWords();
  string s = FileReader::readFasta("data/Thermotoga_petrophila.fa");
  vector<string> result = BioInf::frequentWords(s, 9);
  for (string s : result) {
    cout << s << endl;
  }

  return 0;
}

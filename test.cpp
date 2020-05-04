#include "bioinf.h"
#include "filereader.h"

#include <iostream>
#include <map>
#include <cassert>
#include <chrono>
#include <algorithm>
using namespace std;

class TimeUtil {
private:
  static std::map<std::string, double> results;
public:
  static void start();
};

void testKmer() {
  string t = "CTATTTGCTCTA";
  std::vector<std::string> kmers = BioInf::kmer(t, 3);
  int expectedValue = 10;
  assert(kmers.size() == expectedValue);
}

/**
 * Test method for the pattern count method.
 */
void testPatternCount() {
  string t = "CTATTTGCTCTATTTGGTGCTATTTGCTATTTGTCCTATTTGCCTATTTGCTATTTGAACTATTTGCTATTTGCCTATTTGTCTATTTGCTATTTGCTATTTGCCTATTTGACTATTTGTCTATTTGACTATTTGTCCCTATTTGAACTATTTGGGTAACAGCTATTTGTCGTACTACCTATTTGCAGAGCCCTATTTGAACCCTATTTGCTATTTGAAACCAACTATTTGGTGTAATGTCTCTACTATTTGCTATTTGACTATTTGACCCTATTTGCTATTTGCGCTATTTGCTATTTGGTCTATTTGCTATTTGTCCTATTTGTATACTATTTGCTGCTATTTGACTATTTGCTCTTCTATTTGGACTGGGCTATTTGCTCTATTTGCTATTTGTTCCTATTTGCTATTTGCTCTATTTGTCTATTTGCTATTTGATCTATTTGCTATTTGGTTACTATTTGCGACTATTTGCTATTTGCCTATTTGCTATTTGAACTATTTGTGGGTGCTATTTGCTATTTGCTATTTGAACTATTTGCTATTTGTGGCCACTATTTGCGCTATTTGCCTATTTGCGCTATTTGCGGAGACTATTTGCTATTTGCTATTTGATGGCTATTTGCTATTTGCTATTTGTGATCTATTTGGGGTGCTTACCCTATTTGCTTTTGTTCCTATTTGGCTATTTGAATTACTGGTCCTATTTGCTATTTGTGCCTATTTGACGTGCTGCTATTTGCTATTTGCCTGGCTTCTATTTGCGCTATTTGTTGAGACTATTTGGGATAATCTATTTGAACGCTATTTGGTACTCCACCGGCCTATTTGCTGAGCTATTTGCTATTTGTTATGCTGTAATCTATTTGAACTATTTGGTCTATTTGACTATTTGTTCTATTTGTACACTATTTGTCTATTTGAAAACCCCTATTTGCGTCTATTTGCTATTTGCGAGGTCTATTTGCTATTTGTCCCTATTTGGCCTATTTGCTATTTGCTATTTGCTATTTGCTATTTGTCCACTATTTGGAACTATTTGCTATTTG";
  string p = "CTATTTGCT";

  int expectedValue = 40;
  int value = BioInf::patternCount(t, p);
  std::vector<int> indices = BioInf::patternMatch(t, p);

  assert(value == expectedValue);
  assert(indices.size() == expectedValue);
}

/**
 * Test method for finding the most frequent word.
 */
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

void testFindClumps() {
  string sequence = "CGGACTCGACAGATGTGAAGAACGACAATGTGAAGACTCGACACGACAGAGTGAAGAGAAGAGGAAACATTGTAA";
  vector<string> expectedValues;
  expectedValues.push_back("CGACA");
  expectedValues.push_back("GAAGA");
  vector<string> value = BioInf::findClumps(sequence, 5, 50, 4);
  for (string s : value) {
    assert(std::find(expectedValues.begin(), expectedValues.end(), s) != expectedValues.end());
  }
  assert(expectedValues.size() == value.size());
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

void performanceFindClumps() {
  auto start = std::chrono::system_clock::now();
  string sequence = FileReader::read("data/E_coli.txt");
  vector<string> value = BioInf::findClumps(sequence, 9, 500, 3);
  auto stop = std::chrono::system_clock::now();
}


int main(int argc, char **argv) {
  testKmer();
  testPatternCount();
  testFrequentWords();
  testReverseComplement();
  testFindClumps();

  //performanceFrequentWords();
  //performanceFindClumps();



  return 0;
}

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

#include "bioinf.h"
#include "filereader.h"
#include "filewriter.h"
#include "util.h"
#include "debrujin.h"

#include <iostream>
#include <map>
#include <cassert>
#include <chrono>
#include <algorithm>
using namespace std;

string createRandomDNA(int length) {
  char alphabet[] = {'A', 'C', 'G', 'T'};
  string result;
  for (int i=0; i<length; i++) {
    result.push_back(alphabet[rand()%4]);
  }
  return result;
}

void testKmer() {
  string t = "CTATTTGCTCTA";
  int kmerLength = 3;
  std::vector<std::string> kmers = BioInf::kmer(t, kmerLength);
  int expectedValue = 10;
  assert(kmers.size() == expectedValue);
  string lastKmer = t.substr(t.size()-kmerLength, kmerLength);
  assert(lastKmer == kmers.at(kmers.size()-1));
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

void testSplitSequence() {
  //string sequence = "ACGTTGCATGTCGCATGATGCATGAGAGCT";
  //const int length = 6;
  string sequence = FileReader::read("data/Vibrio_cholerae.txt");
  const int length = 50;
  vector<string> values = Util::splitSequence(sequence, length);
  //FileWriter::writeLines(values, "reads.txt");

  // check for the first and last substring
  string first = sequence.substr(0, length);
  string last = sequence.substr(sequence.size() - length, length);

  bool firstFound = false;
  bool lastFound = false;
  for (string s : values) {
    if (s == first) {
      firstFound = true;
    }
    else if (s == last) {
      lastFound = true;
    }
    if (firstFound && lastFound) {
      break;
    }
  }
  assert(firstFound);
  assert(lastFound);

}



void testGenomeAssembly() {
  string sequence = "TAATGCCATGGGATGTT";
  int kmerLength = 3;
  //string sequence = "TGACAGGGACCCTCTTGTATAGCAGCAGTTGTGCATTTGTTGCCACTCATAGCCTTCCGATGGAGAGAAGCGCGGGCCACTAGAAGATAATGTCGGGCCCTTGAGCGCGCCAAGCCCCAGGCATTTGTAGGCAGGTTTCCT";
  //int kmerLength = 6;
  std::vector<std::string> kmers = BioInf::kmer(sequence, kmerLength);

  // store kmers in file
  //FileWriter::writeLines(kmers, "reads.txt");

  string result = BioInf::assemblyGenome(kmers);
  assert(sequence == result);

  // brute force testing
  const int N = 10;
  for (int i=0; i<N; i++) {
    sequence = createRandomDNA(rand() % 100 + 100);
    kmerLength = rand() % 10 + 3;
    kmers = BioInf::kmer(sequence, kmerLength);
    result = BioInf::assemblyGenome(kmers);
    assert(sequence == result);
  }
}

void performanceGenomeAssembly() {
  auto start = std::chrono::system_clock::now();
  string sequence = FileReader::read("data/E_coli.txt");
  int kmerLength = 20;
  std::vector<std::string> kmers = BioInf::kmer(sequence, kmerLength);
  string result = BioInf::assemblyGenome(kmers);
  assert(sequence == result);
  auto stop = std::chrono::system_clock::now();
}

int main(int argc, char **argv) {

  testGenomeAssembly();
  performanceGenomeAssembly();

  //testSplitSequence();
  //testKmer();
  //testPatternCount();
  //testFrequentWords();
  //testReverseComplement();
  //testFindClumps();

  //performanceFrequentWords();
  //performanceFindClumps();

  return 0;
}

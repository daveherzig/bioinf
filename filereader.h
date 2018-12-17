#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>

class FileReader {
public:
  static std::vector<std::string> readLines(std::string filename);
  static std::string concat(std::vector<std::string> lines);
};

#endif


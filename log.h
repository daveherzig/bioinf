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

Copyright 2018, David Herzig (dave.herzig@gmail.com)
***/

#ifndef LOG_H
#define LOG_H

#include <string>

class Log {
private:
  static int level;
  static int output;
  static std::string filename;

  static void printMessage(std::string msg);

public:
  // defining levels
  static const int DEBUG = 0;
  static const int INFO = 1;
  static const int WARNING = 2;
  static const int ERROR = 3;
  static const int FATAL = 4;
  static const int NONE = 5;

  // defining output location
  static const int CONOSLE = 0x00000001;
  static const int FILE = 0x00000010;

  static void setLevel(int level);
  static void setOutput(int output);
  static void setFilename(std::string filename);

  static void debug(std::string msg);
  static void info(std::string msg);
  static void warning(std::string msg);
  static void error(std::string msg);
  static void fatal(std::string msg);
};

#endif

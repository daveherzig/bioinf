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

#include "log.h"

int Log::level = 0;
int Log::output = CONOSLE;
std::string Log::filename = "output.log";

void Log::setLevel(int level) {
  Log::level = level;
}

void Log::setFilename(std::string filename) {

}

void Log::debug(std::string msg) {

}

void Log::info(std::string msg) {

}

void Log::warning(std::string msg) {

}

void Log::error(std::string msg) {

}

void Log::fatal(std::string msg) {

}

void Log::printMessage(std::string msg) {

}

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

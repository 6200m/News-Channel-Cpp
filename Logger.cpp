//
// Created by void on 8/20/18.
//

#include "Logger.h"

Logger::~Logger() {
 std::lock_guard<std::mutex> lock(printerLock);
 std::cerr << error.str();
 std::cout << info.str();
}

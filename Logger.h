//
// Created by void on 8/20/18.
//

#ifndef FILE_MAKER_LOGGER_H
#define FILE_MAKER_LOGGER_H

#include <iostream>
#include <sstream>
#include <mutex>

// Attempt at preventing jumbling when printing from multiple threads
class Logger final {
 std::mutex printerLock;
public:
 std::ostringstream info;
 std::ostringstream error;
 Logger() = default;
 ~Logger();
};


#endif //FILE_MAKER_LOGGER_H

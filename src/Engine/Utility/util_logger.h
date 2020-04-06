//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  This logger uses the internal logger module to give logging access to the
//  user.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_UTIL_LOGGER_H_
#define FASTENGINE_UTIL_LOGGER_H_

#include "../Logger/logger.h"

namespace logger {

void log(std::string message) {
  fast_engine::Logger::getInstance()->log(message);
}
void logWarning(std::string message) {
  fast_engine::Logger::getInstance()->logWarning(message);
}
void logError(std::string message) {
  fast_engine::Logger::getInstance()->logError(message);
}
void logFatalError(std::string message,
                   std::logic_error customError =
                       std::logic_error(fe_config::DEFAULT_ERROR_MESSAGE)) {
  fast_engine::Logger::getInstance()->logFatalError(message, customError);
}

void log(double message) { fast_engine::Logger::getInstance()->log(message); }
void logWarning(double message) {
  fast_engine::Logger::getInstance()->logWarning(message);
}
void logError(double message) {
  fast_engine::Logger::getInstance()->logError(message);
}
void logFatalError(double message,
                   std::logic_error customError =
                       std::logic_error(fe_config::DEFAULT_ERROR_MESSAGE)) {
  fast_engine::Logger::getInstance()->logFatalError(message, customError);
}

} // namespace logger

#endif

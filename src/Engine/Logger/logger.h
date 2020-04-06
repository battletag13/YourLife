//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Logging module provides a system to log engine status.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_LOGGER_H_
#define FASTENGINE_LOGGER_H_

#include <stdexcept>
#include <string>

#include "../config.h"

namespace fast_engine {

std::string timeAsString();

class Logger {
public:
  ~Logger();

  static Logger *getInstance() {
    return loggerInstance =
               (loggerInstance == nullptr ? new Logger() : loggerInstance);
  }

  void log(std::string message);
  void logWarning(std::string message);
  void logError(std::string message);
  void logFatalError(std::string message,
                     std::logic_error customError =
                         std::logic_error(fe_config::DEFAULT_ERROR_MESSAGE));

  void log(double message);
  void logWarning(double message);
  void logError(double message);
  void logFatalError(double message,
                     std::logic_error customError =
                         std::logic_error(fe_config::DEFAULT_ERROR_MESSAGE));

private:
  Logger();
  static Logger *loggerInstance;
};

} // namespace fast_engine
#endif

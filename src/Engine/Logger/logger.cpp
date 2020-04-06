//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Logging module implementation.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "../config.h"
#include "logger.h"

namespace fast_engine {

Logger *Logger::loggerInstance = nullptr;

std::string timeAsString() {
  time_t currentTime = std::time(0);
  return ctime(&currentTime);
}

Logger::Logger() {
  if (fe_config::LOGGING_TO_FILE) {
    std::ofstream logFile(fe_config::LOG_FILE,
                          std::fstream::out | std::fstream::app);
    logFile << "LOG_BEGIN - " << timeAsString() << "\n\n";
    logFile.close();
  }
}
Logger::~Logger() {
  if (fe_config::LOGGING_TO_FILE) {
    std::ofstream logFile(fe_config::LOG_FILE,
                          std::fstream::out | std::fstream::app);
    logFile << "\nLOG_END - " << timeAsString();
    logFile.close();
  }
}

void Logger::log(std::string message) {
  if (fe_config::LOGGING_TO_FILE) {
    std::ofstream logFile(fe_config::LOG_FILE,
                          std::fstream::out | std::fstream::app);
    logFile << timeAsString() << "STATUS::" << message << "\n\n";
    logFile.close();
  }

  std::clog << "STATUS::" << message << '\n';
}

void Logger::logWarning(std::string message) {
  if (fe_config::LOGGING_TO_FILE) {
    std::ofstream logFile(fe_config::LOG_FILE,
                          std::fstream::out | std::fstream::app);
    logFile << timeAsString() << "WARN::" << message << "\n\n";
    logFile.close();
  }

  std::clog << "WARNING::" << message << '\n';
}

void Logger::logError(std::string message) {

  if (fe_config::LOGGING_TO_FILE) {
    std::ofstream logFile(fe_config::LOG_FILE,
                          std::fstream::out | std::fstream::app);
    logFile << timeAsString() << "ERROR::" << message << "\n\n";
    logFile.close();
  }

  std::cerr << "ERROR::" << message << '\n';
}

void Logger::logFatalError(std::string message, std::logic_error customError) {

  if (std::string(customError.what()) == fe_config::DEFAULT_ERROR_MESSAGE) {
    customError = std::logic_error(message);
  }

  if (fe_config::LOGGING_TO_FILE) {
    std::ofstream logFile(fe_config::LOG_FILE,
                          std::fstream::out | std::fstream::app);
    logFile << timeAsString() << "FATAL_ERROR::" << message << "\n\n";
    logFile.close();
  }

  std::cerr << "FATAL_ERROR::" << message << '\n';
  throw customError;
}

void Logger::log(double message) {
  if (fe_config::LOGGING_TO_FILE) {
    std::ofstream logFile(fe_config::LOG_FILE,
                          std::fstream::out | std::fstream::app);
    logFile << timeAsString() << "STATUS::" << message << "\n\n";
    logFile.close();
  }

  std::clog << "STATUS::" << message << '\n';
}

void Logger::logWarning(double message) {
  if (fe_config::LOGGING_TO_FILE) {
    std::ofstream logFile(fe_config::LOG_FILE,
                          std::fstream::out | std::fstream::app);
    logFile << timeAsString() << "WARN::" << message << "\n\n";
    logFile.close();
  }

  std::clog << "WARNING::" << message << '\n';
}

void Logger::logError(double message) {

  if (fe_config::LOGGING_TO_FILE) {
    std::ofstream logFile(fe_config::LOG_FILE,
                          std::fstream::out | std::fstream::app);
    logFile << timeAsString() << "ERROR::" << message << "\n\n";
    logFile.close();
  }

  std::cerr << "ERROR::" << message << '\n';
}

void Logger::logFatalError(double message, std::logic_error customError) {

  if (std::string(customError.what()) == fe_config::DEFAULT_ERROR_MESSAGE) {
    customError = std::logic_error(std::to_string(message));
  }

  if (fe_config::LOGGING_TO_FILE) {
    std::ofstream logFile(fe_config::LOG_FILE,
                          std::fstream::out | std::fstream::app);
    logFile << timeAsString() << "FATAL_ERROR::" << message << "\n\n";
    logFile.close();
  }

  std::cerr << "FATAL_ERROR::" << message << '\n';
  throw customError;
}

} // namespace fast_engine

//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Time module implementation.
//
//  Copyright © 2019 Matthew Lin. All rights reserved.
//
#include "time.h"

double time::deltaTime;

// Set the start point to the current time
void Timer::start() { startPoint = std::chrono::high_resolution_clock::now(); }
// Set the end point to the current time
void Timer::stop() {
  endPoint = std::chrono::high_resolution_clock::now();
  duration += std::chrono::duration_cast<std::chrono::microseconds>(endPoint -
                                                                    startPoint)
                  .count();
  start();
}

// Count doesn't actually stop timer,
// just updates the endPoint variable with stop()
long double MicrosecondsTimer::count() {
  stop();
  return duration;
}
long double MicrosecondsTimer::reset() {
  stop();
  double toReturn = duration;
  duration = 0;
  start();
  return toReturn;
}

long double MilisecondsTimer::count() {
  stop();
  return duration / 1000.;
}
long double MilisecondsTimer::reset() {
  stop();
  double toReturn = duration;
  duration = 0;
  start();
  return toReturn / 1000.;
}

long double SecondsTimer::count() {
  stop();
  return duration / 1000000.;
}
long double SecondsTimer::reset() {
  stop();
  double toReturn = duration;
  duration = 0;
  start();
  return toReturn / 1000000.;
}

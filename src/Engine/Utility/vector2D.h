//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  A simple class which holds an x and y variable. Supports basic operations
//  like +, -, *, / & their compount assignment counterparts.
//
//  Copyright © 2020 Matthew Lin. All rights reserved.
//
#ifndef FASTENGINE_VECTOR2D_H_
#define FASTENGINE_VECTOR2D_H_

struct Vector2D {
  // Constructors
  Vector2D();
  Vector2D(double x, double y);

  // Utility
  friend Vector2D operator+(const Vector2D &v1, const Vector2D &v2);
  friend Vector2D operator-(const Vector2D &v1, const Vector2D &v2);
  friend Vector2D operator*(const Vector2D &v1, const Vector2D &v2);
  friend Vector2D operator/(const Vector2D &v1, const Vector2D &v2);

  friend Vector2D operator+(const Vector2D &v1, const double scalar);
  friend Vector2D operator+(const double scalar, const Vector2D &v2);
  friend Vector2D operator-(const Vector2D &v1, const double scalar);
  friend Vector2D operator*(const Vector2D &v1, const double scalar);
  friend Vector2D operator*(const double scalar, const Vector2D &v2);
  friend Vector2D operator/(const Vector2D &v1, const double scalar);

  Vector2D &operator+=(const Vector2D &other);
  Vector2D &operator-=(const Vector2D &other);
  Vector2D &operator*=(const Vector2D &other);
  Vector2D &operator/=(const Vector2D &other);

  Vector2D &operator+=(const double scalar);
  Vector2D &operator-=(const double scalar);
  Vector2D &operator*=(const double scalar);
  Vector2D &operator/=(const double scalar);

  // Members
  double x;
  double y;
};

Vector2D operator+(const Vector2D &v1, const Vector2D &v2);
Vector2D operator-(const Vector2D &v1, const Vector2D &v2);
Vector2D operator*(const Vector2D &v1, const Vector2D &v2);
Vector2D operator/(const Vector2D &v1, const Vector2D &v2);

Vector2D operator+(const Vector2D &v1, const double scalar);
Vector2D operator+(const double scalar, const Vector2D &v2);
Vector2D operator-(const Vector2D &v1, const double scalar);
Vector2D operator*(const Vector2D &v1, const double scalar);
Vector2D operator*(const double scalar, const Vector2D &v2);
Vector2D operator/(const Vector2D &v1, const double scalar);

#endif

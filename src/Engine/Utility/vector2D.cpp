//  FastEngine
//
//  Created by Matthew Lin.
//  Contact: matthewlinplusprogramming@gmail.com
//
//  Vector2D class implementation
//
//  Copyright © 2020 plusprogramming. All rights reserved.
//
#include "vector2D.h"

Vector2D::Vector2D() : x(0), y(0) {}

Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

Vector2D operator+(const Vector2D &v1, const Vector2D &v2) {
  return Vector2D(v1.x + v2.x, v1.y + v2.y);
}
Vector2D operator-(const Vector2D &v1, const Vector2D &v2) {
  return Vector2D(v1.x - v2.x, v1.y - v2.y);
}
Vector2D operator*(const Vector2D &v1, const Vector2D &v2) {
  return Vector2D(v1.x * v2.x, v1.y * v2.y);
}
Vector2D operator/(const Vector2D &v1, const Vector2D &v2) {
  return Vector2D(v1.x / v2.x, v1.y / v2.y);
}
Vector2D operator+(const Vector2D &v1, const double scalar) {
  return Vector2D(v1.x + scalar, v1.y + scalar);
}
Vector2D operator+(const double scalar, const Vector2D &v2) {
  return Vector2D(v2.x + scalar, v2.y + scalar);
}
Vector2D operator-(const Vector2D &v1, const double scalar) {
  return Vector2D(v1.x - scalar, v1.y - scalar);
}
Vector2D operator*(const Vector2D &v1, const double scalar) {
  return Vector2D(v1.x * scalar, v1.y * scalar);
}
Vector2D operator*(const double scalar, const Vector2D &v2) {
  return Vector2D(v2.x * scalar, v2.y * scalar);
}
Vector2D operator/(const Vector2D &v1, const double scalar) {
  return Vector2D(v1.x / scalar, v1.y / scalar);
}

Vector2D &Vector2D::operator+=(const Vector2D &other) {
  this->x += other.x;
  this->y += other.y;
  return *this;
}
Vector2D &Vector2D::operator-=(const Vector2D &other) {
  this->x -= other.x;
  this->y -= other.y;
  return *this;
}
Vector2D &Vector2D::operator*=(const Vector2D &other) {
  this->x *= other.x;
  this->y *= other.y;
  return *this;
}
Vector2D &Vector2D::operator/=(const Vector2D &other) {
  this->x /= other.x;
  this->y /= other.y;
  return *this;
}

Vector2D &Vector2D::operator+=(const double scalar) {
  this->x += scalar;
  this->y += scalar;
  return *this;
}
Vector2D &Vector2D::operator-=(const double scalar) {
  this->x -= scalar;
  this->y -= scalar;
  return *this;
}
Vector2D &Vector2D::operator*=(const double scalar) {
  this->x *= scalar;
  this->y *= scalar;
  return *this;
}
Vector2D &Vector2D::operator/=(const double scalar) {
  this->x /= scalar;
  this->y /= scalar;
  return *this;
}

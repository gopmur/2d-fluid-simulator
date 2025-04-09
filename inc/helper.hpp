#pragma once

#include <cmath>
#include <concepts>
#include "fluid.hpp"

template <typename T>
concept arithmetic_concept = std::integral<T> or std::floating_point<T>;

template <typename T>
  requires arithmetic_concept<T>
class Vector2d {
 private:
  // the same as i
  T x;
  // the same as j
  T y;

 public:
  inline Vector2d(T x, T y);
  inline Vector2d();

  // getters
  inline T get_x() const;
  inline T get_y() const;

  // setters
  inline void set_x(T x);
  inline void set_y(T y);

  inline Vector2d<T> operator+(const Vector2d<T>& other);
  inline Vector2d<T> operator-(const Vector2d<T>& other);

  template <typename G>
    requires arithmetic_concept<G>
  friend Vector2d<T> operator*(const Vector2d<T>& vector, G scalar) {
    return Vector2d<T>(vector.x * scalar, vector.y * scalar);
  }
};

template <typename T>
  requires arithmetic_concept<T>
inline Vector2d<T> Vector2d<T>::operator+(const Vector2d<T>& other) {
  return Vector2d<T>(this->x + other.x, this->y + other.y);
}

template <typename T>
  requires arithmetic_concept<T>
inline Vector2d<T> Vector2d<T>::operator-(const Vector2d<T>& other) {
  return Vector2d<T>(this->x - other.x, this->y - other.y);
}

template <typename T>
  requires arithmetic_concept<T>
inline Vector2d<T>::Vector2d(T x, T y) : x(x), y(y) {}

template <typename T>
  requires arithmetic_concept<T>
inline Vector2d<T>::Vector2d() : x(0), y(0) {}

template <typename T>
  requires arithmetic_concept<T>
inline T Vector2d<T>::get_x() const {
  return x;
}

template <typename T>
  requires arithmetic_concept<T>
inline T Vector2d<T>::get_y() const {
  return y;
}

template <typename T>
  requires arithmetic_concept<T>
inline void Vector2d<T>::set_x(T x) {
  this->x = x;
}

template <typename T>
  requires arithmetic_concept<T>
inline void Vector2d<T>::set_y(T y) {
  this->y = y;
}

template <typename T>
inline float get_distance(Vector2d<T> a, Vector2d<T> b) {
  return std::sqrt((a.get_x() - b.get_x()) * (a.get_x() - b.get_x()) +
                   (a.get_y() - b.get_y()) * (a.get_y() - b.get_y()));
}
#include "Vector2D.h"

Vector2D::Vector2D() : x(0.0f), y(0.0f) {}

Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

Vector2D &Vector2D::Add(const Vector2D &vec) {
  x += vec.x;
  y += vec.y;
  return *this;
}

Vector2D &Vector2D::Subtract(const Vector2D &vec) {
  x -= vec.x;
  y -= vec.y;
  return *this;
}

Vector2D &Vector2D::Multiply(const Vector2D &vec) {
  x *= vec.x;
  y *= vec.y;
  return *this;
}

Vector2D &Vector2D::Divide(const Vector2D &vec) {
  if (vec.x != 0.0f)
    x /= vec.x;
  else
    x = 0.0f;
  if (vec.y != 0.0f)
    y /= vec.y;
  else
    y = 0.0f;
  return *this;
}

Vector2D &Vector2D::operator+=(const Vector2D &vec) { return Add(vec); }

Vector2D &Vector2D::operator-=(const Vector2D &vec) { return Subtract(vec); }

Vector2D &Vector2D::operator*=(const Vector2D &vec) { return Multiply(vec); }

Vector2D &Vector2D::operator/=(const Vector2D &vec) { return Divide(vec); }

Vector2D &Vector2D::operator*=(float scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}

Vector2D &Vector2D::operator*=(int scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}

Vector2D Vector2D::Zero() { return Vector2D(0.0f, 0.0f); }

// Non-member operators
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
  return Vector2D(v2.x != 0.0f ? v1.x / v2.x : 0.0f,
                  v2.y != 0.0f ? v1.y / v2.y : 0.0f);
}

Vector2D operator*(const Vector2D &v, float scalar) {
  return Vector2D(v.x * scalar, v.y * scalar);
}

Vector2D operator*(float scalar, const Vector2D &v) {
  return Vector2D(v.x * scalar, v.y * scalar);
}

Vector2D operator*(const Vector2D &v, int scalar) {
  return Vector2D(v.x * scalar, v.y * scalar);
}

Vector2D operator*(int scalar, const Vector2D &v) {
  return Vector2D(v.x * scalar, v.y * scalar);
}

std::ostream &operator<<(std::ostream &stream, const Vector2D &vec) {
  stream << "(" << vec.x << "," << vec.y << ")";
  return stream;
}
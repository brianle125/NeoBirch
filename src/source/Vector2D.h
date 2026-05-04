#pragma once
#include <iostream>

class Vector2D
{
public:
    float x;
    float y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D& Add(const Vector2D& vec);
    Vector2D& Subtract(const Vector2D& vec);
    Vector2D& Multiply(const Vector2D& vec);
    Vector2D& Divide(const Vector2D& vec);

    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D& operator/=(const Vector2D& vec);

    Vector2D& operator*=(float scalar);
    Vector2D& operator*=(int scalar);

    Vector2D Zero();

    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};

// Non-member operators
Vector2D operator+(const Vector2D& v1, const Vector2D& v2);
Vector2D operator-(const Vector2D& v1, const Vector2D& v2);
Vector2D operator*(const Vector2D& v1, const Vector2D& v2);
Vector2D operator/(const Vector2D& v1, const Vector2D& v2);

Vector2D operator*(const Vector2D& v, float scalar);
Vector2D operator*(float scalar, const Vector2D& v);
Vector2D operator*(const Vector2D& v, int scalar);
Vector2D operator*(int scalar, const Vector2D& v);
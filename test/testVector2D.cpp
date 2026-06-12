#include "Vector2D.h"
#include <gtest/gtest.h>

class Vector2DTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Called before each test
  }

  void TearDown() override {
    // Called after each test
  }
};

TEST_F(Vector2DTest, DefaultConstructor) {
  Vector2D v;
  EXPECT_FLOAT_EQ(v.x, 0.0f);
  EXPECT_FLOAT_EQ(v.y, 0.0f);
}

TEST_F(Vector2DTest, ParameterizedConstructor) {
  Vector2D v(3.5f, 7.2f);
  EXPECT_FLOAT_EQ(v.x, 3.5f);
  EXPECT_FLOAT_EQ(v.y, 7.2f);
}


TEST_F(Vector2DTest, AddVector) {
  Vector2D v1(2,4);
  Vector2D v2(2,4);
  
  v1.Add(v2);

  Vector2D expected(4, 8);
  EXPECT_EQ(v1.x, expected.x);
  EXPECT_EQ(v1.y, expected.y);
}

TEST_F(Vector2DTest, SubVector) {
  Vector2D v1(2,4);
  Vector2D v2(2,4);
  
  v1.Subtract(v2);

  Vector2D expected(0, 0);;;
  EXPECT_EQ(v1.x, expected.x);
  EXPECT_EQ(v1.y, expected.y);
}

TEST_F(Vector2DTest, MultiplyVectors) {
  Vector2D v1(2.0f, 3.0f);
  Vector2D v2(4.0f, 5.0f);
  
  v1.Multiply(v2);

  Vector2D expected(8.0f, 15.0f);
  EXPECT_FLOAT_EQ(v1.x, expected.x);
  EXPECT_FLOAT_EQ(v1.y, expected.y);
}

TEST_F(Vector2DTest, DivideVectors) {
  Vector2D v1(8.0f, 16.0f);
  Vector2D v2(2.0f, 4.0f);
  
  v1.Divide(v2);

  Vector2D expected(4.0f, 4.0f);
  EXPECT_FLOAT_EQ(v1.x, expected.x);
  EXPECT_FLOAT_EQ(v1.y, expected.y);
}

TEST_F(Vector2DTest, AdditionOperator) {
  Vector2D v1(1.0f, 2.0f);
  Vector2D v2(3.0f, 4.0f);
  
  Vector2D result = v1 + v2;

  EXPECT_FLOAT_EQ(result.x, 4.0f);
  EXPECT_FLOAT_EQ(result.y, 6.0f);
}

TEST_F(Vector2DTest, SubtractionOperator) {
  Vector2D v1(5.0f, 7.0f);
  Vector2D v2(2.0f, 3.0f);
  
  Vector2D result = v1 - v2;

  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, 4.0f);
}

TEST_F(Vector2DTest, MultiplicationOperator) {
  Vector2D v1(2.0f, 3.0f);
  Vector2D v2(4.0f, 5.0f);
  
  Vector2D result = v1 * v2;

  EXPECT_FLOAT_EQ(result.x, 8.0f);
  EXPECT_FLOAT_EQ(result.y, 15.0f);
}

TEST_F(Vector2DTest, DivisionOperator) {
  Vector2D v1(10.0f, 20.0f);
  Vector2D v2(2.0f, 4.0f);
  
  Vector2D result = v1 / v2;

  EXPECT_FLOAT_EQ(result.x, 5.0f);
  EXPECT_FLOAT_EQ(result.y, 5.0f);
}

TEST_F(Vector2DTest, ScalarMultiplicationFloat) {
  Vector2D v(2.0f, 3.0f);
  
  Vector2D result = v * 2.5f;

  EXPECT_FLOAT_EQ(result.x, 5.0f);
  EXPECT_FLOAT_EQ(result.y, 7.5f);
}

TEST_F(Vector2DTest, ScalarMultiplicationFloatLeft) {
  Vector2D v(2.0f, 3.0f);
  
  Vector2D result = 2.5f * v;

  EXPECT_FLOAT_EQ(result.x, 5.0f);
  EXPECT_FLOAT_EQ(result.y, 7.5f);
}

TEST_F(Vector2DTest, ScalarMultiplicationInt) {
  Vector2D v(2.0f, 3.0f);
  
  Vector2D result = v * 3;

  EXPECT_FLOAT_EQ(result.x, 6.0f);
  EXPECT_FLOAT_EQ(result.y, 9.0f);
}

TEST_F(Vector2DTest, ScalarMultiplicationIntLeft) {
  Vector2D v(2.0f, 3.0f);
  
  Vector2D result = 3 * v;

  EXPECT_FLOAT_EQ(result.x, 6.0f);
  EXPECT_FLOAT_EQ(result.y, 9.0f);
}

TEST_F(Vector2DTest, CompoundAdditionOperator) {
  Vector2D v1(1.0f, 2.0f);
  Vector2D v2(3.0f, 4.0f);
  
  v1 += v2;

  EXPECT_FLOAT_EQ(v1.x, 4.0f);
  EXPECT_FLOAT_EQ(v1.y, 6.0f);
}

TEST_F(Vector2DTest, CompoundSubtractionOperator) {
  Vector2D v1(5.0f, 7.0f);
  Vector2D v2(2.0f, 3.0f);
  
  v1 -= v2;

  EXPECT_FLOAT_EQ(v1.x, 3.0f);
  EXPECT_FLOAT_EQ(v1.y, 4.0f);
}

TEST_F(Vector2DTest, CompoundMultiplicationOperator) {
  Vector2D v1(2.0f, 3.0f);
  Vector2D v2(4.0f, 5.0f);
  
  v1 *= v2;

  EXPECT_FLOAT_EQ(v1.x, 8.0f);
  EXPECT_FLOAT_EQ(v1.y, 15.0f);
}

TEST_F(Vector2DTest, CompoundDivisionOperator) {
  Vector2D v1(10.0f, 20.0f);
  Vector2D v2(2.0f, 4.0f);
  
  v1 /= v2;

  EXPECT_FLOAT_EQ(v1.x, 5.0f);
  EXPECT_FLOAT_EQ(v1.y, 5.0f);
}

TEST_F(Vector2DTest, CompoundScalarMultiplicationFloat) {
  Vector2D v(2.0f, 3.0f);
  
  v *= 2.5f;

  EXPECT_FLOAT_EQ(v.x, 5.0f);
  EXPECT_FLOAT_EQ(v.y, 7.5f);
}

TEST_F(Vector2DTest, CompoundScalarMultiplicationInt) {
  Vector2D v(2.0f, 3.0f);
  
  v *= 3;

  EXPECT_FLOAT_EQ(v.x, 6.0f);
  EXPECT_FLOAT_EQ(v.y, 9.0f);
}

TEST_F(Vector2DTest, ZeroMethod) {
  Vector2D v = Vector2D(5.0f, 10.0f).Zero();

  EXPECT_FLOAT_EQ(v.x, 0.0f);
  EXPECT_FLOAT_EQ(v.y, 0.0f);
}

TEST_F(Vector2DTest, DistanceFromOrigin) {
  Vector2D v1(0.0f, 0.0f);
  Vector2D v2(3.0f, 4.0f);

  float d = v1.dist(v2);
  EXPECT_FLOAT_EQ(d, 5.0f);
}

TEST_F(Vector2DTest, DistanceBetweenTwoVectors) {
  Vector2D v1(2,4);
  Vector2D v2(2,4);

  float d = v1.dist(v2);
  EXPECT_FLOAT_EQ(d, sqrt(80));
  EXPECT_FLOAT_EQ(dist(v1, v2), d);
}

TEST_F(Vector2DTest, DistanceBetweenNegativeVectors) {
  Vector2D v1(-1.0f, -1.0f);
  Vector2D v2(-4.0f, -5.0f);

  float d = v1.dist(v2);
  EXPECT_FLOAT_EQ(d, 5.0f);
}
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
#include "ECS/ECS.h"

// Test components
class PositionComponent : public Component {
public:
  float x = 0.0f;
  float y = 0.0f;

  PositionComponent(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

  void init() override {
    // Initialization logic
  }
};

class VelocityComponent : public Component {
public:
  float vx = 0.0f;
  float vy = 0.0f;

  VelocityComponent(float vx = 0.0f, float vy = 0.0f) : vx(vx), vy(vy) {}

  void init() override {
    // Initialization logic
  }
};

class HealthComponent : public Component {
public:
  int hp = 100;

  HealthComponent(int hp = 100) : hp(hp) {}

  void init() override {
    // Initialization logic
  }
};

// Test fixture
class ECSComponentTest : public ::testing::Test {
protected:
  Manager manager;

  void SetUp() override {
    // Called before each test
  }

  void TearDown() override {
    // Called after each test
  }
};
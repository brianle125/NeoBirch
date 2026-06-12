#include <gtest/gtest.h>
#include "testComponents.h"

// Tests for adding components
TEST_F(ECSComponentTest, AddSingleComponent) {
  Entity &entity = manager.addEntity();
  PositionComponent &pos = entity.addComponent<PositionComponent>(10.0f, 20.0f);

  EXPECT_TRUE(entity.hasComponent<PositionComponent>());
  EXPECT_EQ(pos.x, 10.0f);
  EXPECT_EQ(pos.y, 20.0f);
}

TEST_F(ECSComponentTest, AddMultipleComponents) {
  Entity &entity = manager.addEntity();
  entity.addComponent<PositionComponent>(5.0f, 15.0f);
  entity.addComponent<VelocityComponent>(1.0f, 2.0f);
  entity.addComponent<HealthComponent>(50);

  EXPECT_TRUE(entity.hasComponent<PositionComponent>());
  EXPECT_TRUE(entity.hasComponent<VelocityComponent>());
  EXPECT_TRUE(entity.hasComponent<HealthComponent>());
}

TEST_F(ECSComponentTest, GetComponentAfterAdding) {
  Entity &entity = manager.addEntity();
  entity.addComponent<PositionComponent>(7.0f, 8.0f);

  PositionComponent &pos = entity.getComponent<PositionComponent>();
  EXPECT_EQ(pos.x, 7.0f);
  EXPECT_EQ(pos.y, 8.0f);
}

TEST_F(ECSComponentTest, AddComponentWithDefaultValues) {
  Entity &entity = manager.addEntity();
  entity.addComponent<HealthComponent>();

  HealthComponent &health = entity.getComponent<HealthComponent>();
  EXPECT_EQ(health.hp, 100);
}

// Tests for removing components
TEST_F(ECSComponentTest, RemoveComponent) {
  Entity &entity = manager.addEntity();
  entity.addComponent<PositionComponent>(1.0f, 2.0f);

  EXPECT_TRUE(entity.hasComponent<PositionComponent>());

  entity.removeComponent<PositionComponent>();

  EXPECT_FALSE(entity.hasComponent<PositionComponent>());
  EXPECT_EQ(entity.componentCount(), 0);
}

TEST_F(ECSComponentTest, RemoveComponentFromMultipleComponents) {
  Entity &entity = manager.addEntity();
  entity.addComponent<PositionComponent>(1.0f, 2.0f);
  entity.addComponent<VelocityComponent>(3.0f, 4.0f);
  entity.addComponent<HealthComponent>(100);

  EXPECT_TRUE(entity.hasComponent<PositionComponent>());
  EXPECT_TRUE(entity.hasComponent<VelocityComponent>());
  EXPECT_TRUE(entity.hasComponent<HealthComponent>());

  entity.removeComponent<VelocityComponent>();
  
  EXPECT_EQ(entity.componentCount(), 2);
  EXPECT_TRUE(entity.hasComponent<PositionComponent>());
  EXPECT_FALSE(entity.hasComponent<VelocityComponent>());
  EXPECT_TRUE(entity.hasComponent<HealthComponent>());
}

TEST_F(ECSComponentTest, RemoveNonExistentComponent) {
  Entity &entity = manager.addEntity();
  entity.addComponent<PositionComponent>(1.0f, 2.0f);

  // Should not crash when removing a component that doesn't exist
  entity.removeComponent<VelocityComponent>();

  EXPECT_TRUE(entity.hasComponent<PositionComponent>());
  EXPECT_FALSE(entity.hasComponent<VelocityComponent>());
  EXPECT_EQ(entity.componentCount(), 1);
}

TEST_F(ECSComponentTest, AddComponentAfterRemoving) {
  Entity &entity = manager.addEntity();
  entity.addComponent<PositionComponent>(1.0f, 2.0f);
  entity.removeComponent<PositionComponent>();

  EXPECT_FALSE(entity.hasComponent<PositionComponent>());

  PositionComponent &pos = entity.addComponent<PositionComponent>(5.0f, 6.0f);

  EXPECT_TRUE(entity.hasComponent<PositionComponent>());
  EXPECT_EQ(pos.x, 5.0f);
  EXPECT_EQ(pos.y, 6.0f);
}

TEST_F(ECSComponentTest, RemoveAllComponents) {
  Entity &entity = manager.addEntity();
  entity.addComponent<PositionComponent>(1.0f, 2.0f);
  entity.addComponent<VelocityComponent>(3.0f, 4.0f);
  entity.addComponent<HealthComponent>(100);

  entity.removeComponent<PositionComponent>();
  entity.removeComponent<VelocityComponent>();
  entity.removeComponent<HealthComponent>();

  EXPECT_FALSE(entity.hasComponent<PositionComponent>());
  EXPECT_FALSE(entity.hasComponent<VelocityComponent>());
  EXPECT_FALSE(entity.hasComponent<HealthComponent>());
  EXPECT_EQ(entity.componentCount(), 0);
}

TEST_F(ECSComponentTest, ComponentRetainsData) {
  Entity &entity = manager.addEntity();
  PositionComponent &pos = entity.addComponent<PositionComponent>(10.0f, 20.0f);

  pos.x = 15.0f;
  pos.y = 25.0f;

  PositionComponent &retrieved = entity.getComponent<PositionComponent>();
  EXPECT_EQ(retrieved.x, 15.0f);
  EXPECT_EQ(retrieved.y, 25.0f);
}

TEST_F(ECSComponentTest, MultipleEntitiesWithComponents) {
  Entity &entity1 = manager.addEntity();
  Entity &entity2 = manager.addEntity();

  entity1.addComponent<PositionComponent>(1.0f, 2.0f);
  entity2.addComponent<PositionComponent>(5.0f, 6.0f);

  EXPECT_EQ(entity1.getComponent<PositionComponent>().x, 1.0f);
  EXPECT_EQ(entity2.getComponent<PositionComponent>().x, 5.0f);

  entity1.removeComponent<PositionComponent>();

  EXPECT_FALSE(entity1.hasComponent<PositionComponent>());
  EXPECT_TRUE(entity2.hasComponent<PositionComponent>());
}

#include <gtest/gtest.h>

#include "Others/RoundTarget.hpp"

namespace RoundTarget_test {

static constexpr sf::Time elapsedTime = sf::seconds(1.f / 60.f);
constexpr auto notScreenBoundary = 200.f;
constexpr auto radius = 50.f;
constexpr auto speed = 100.f;
constexpr sf::Vector2u windowSize{640, 480};

TEST(RoundTargetTest, die) {
  RoundTarget target{radius, sf::Color::Cyan, 0.f, 0.f, 0.f, 0.f};

  target.die();
  EXPECT_EQ(target.getShape().getFillColor(), sf::Color::Red);

  target.update(elapsedTime, windowSize);
  target.update(elapsedTime, windowSize);

  EXPECT_FLOAT_EQ(radius * static_cast<float>(nbFramesWhenDying - 1) /
                      static_cast<float>(nbFramesWhenDying),
                  target.getShape().getRadius());
  EXPECT_FLOAT_EQ(2.f / static_cast<float>(nbFramesWhenDying),
                  target.getShape().getPosition().x);
  EXPECT_FLOAT_EQ(2.f / static_cast<float>(nbFramesWhenDying),
                  target.getShape().getPosition().y);
}

TEST(RoundTargetTest, isDead_false) {
  RoundTarget target{radius, sf::Color::Cyan, 0.f, 0.f, 0.f, 0.f};

  target.die();
  EXPECT_FALSE(target.isDead());

  target.update(elapsedTime, windowSize);
  target.update(elapsedTime, windowSize);

  EXPECT_FALSE(target.isDead());
}

TEST(RoundTargetTest, isDead_true) {
  RoundTarget target{radius, sf::Color::Cyan, 0.f, 0.f, 0.f, 0.f};

  target.die();

  for (auto i = 0; i < nbFramesWhenDying; ++i) {
    target.update(elapsedTime, windowSize);
  }

  EXPECT_TRUE(target.isDead());
}

TEST(RoundTargetTest, isHitByMouse_true) {
  RoundTarget target{radius, sf::Color::Cyan, 0.f, 0.f, 0.f, 0.f};

  EXPECT_TRUE(target.isHitByMouse(
      {static_cast<int>(radius), static_cast<int>(radius)}));
}

TEST(RoundTargetTest, isHitByMouse_false) {
  RoundTarget target{radius, sf::Color::Cyan, 0.f, 0.f, 0.f, 0.f};

  EXPECT_FALSE(target.isHitByMouse({0, 0}));
}

TEST(RoundTargetTest, update_noBounce) {
  RoundTarget target{
      radius, sf::Color::Cyan, notScreenBoundary, notScreenBoundary, speed,
      speed};

  target.update(elapsedTime, windowSize);
  EXPECT_FLOAT_EQ(notScreenBoundary + speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().x);
  EXPECT_FLOAT_EQ(notScreenBoundary + speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().y);

  target.update(elapsedTime, windowSize);
  EXPECT_FLOAT_EQ(notScreenBoundary + 2 * speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().x);
  EXPECT_FLOAT_EQ(notScreenBoundary + 2 * speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().y);
}

TEST(RoundTargetTest, update_bounceLeft) {
  RoundTarget target{radius, sf::Color::Cyan, 0.f, notScreenBoundary,
                     -speed, -speed};

  target.update(elapsedTime, windowSize);
  EXPECT_FLOAT_EQ(speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().x);
  EXPECT_FLOAT_EQ(notScreenBoundary - speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().y);

  target.update(elapsedTime, windowSize);
  EXPECT_FLOAT_EQ(2 * speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().x);
  EXPECT_FLOAT_EQ(notScreenBoundary - 2 * speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().y);
}

TEST(RoundTargetTest, update_bounceUp) {
  RoundTarget target{radius, sf::Color::Cyan, notScreenBoundary,
                     0.f,    -speed,          -speed};

  target.update(elapsedTime, windowSize);
  EXPECT_FLOAT_EQ(notScreenBoundary - speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().x);
  EXPECT_FLOAT_EQ(speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().y);

  target.update(elapsedTime, windowSize);
  EXPECT_FLOAT_EQ(notScreenBoundary - 2 * speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().x);
  EXPECT_FLOAT_EQ(2 * speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().y);
}

TEST(RoundTargetTest, update_bounceRight) {
  RoundTarget target{radius,
                     sf::Color::Cyan,
                     static_cast<float>(windowSize.x),
                     notScreenBoundary,
                     speed,
                     speed};

  target.update(elapsedTime, windowSize);
  EXPECT_FLOAT_EQ(static_cast<float>(windowSize.x) -
                      4 * target.getShape().getRadius() -
                      speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().x);
  EXPECT_FLOAT_EQ(notScreenBoundary + speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().y);

  target.update(elapsedTime, windowSize);
  EXPECT_FLOAT_EQ(static_cast<float>(windowSize.x) -
                      4 * target.getShape().getRadius() -
                      2 * speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().x);
  EXPECT_FLOAT_EQ(notScreenBoundary + 2 * speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().y);
}

TEST(RoundTargetTest, update_bounceBottom) {
  RoundTarget target{radius,
                     sf::Color::Cyan,
                     notScreenBoundary,
                     static_cast<float>(windowSize.y),
                     speed,
                     speed};

  target.update(elapsedTime, windowSize);
  EXPECT_FLOAT_EQ(notScreenBoundary + speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().x);
  EXPECT_FLOAT_EQ(static_cast<float>(windowSize.y) -
                      4 * target.getShape().getRadius() -
                      speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().y);

  target.update(elapsedTime, windowSize);
  EXPECT_FLOAT_EQ(notScreenBoundary + 2 * speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().x);
  EXPECT_FLOAT_EQ(static_cast<float>(windowSize.y) -
                      4 * target.getShape().getRadius() -
                      2 * speed * elapsedTime.asSeconds(),
                  target.getShape().getPosition().y);
}
}  // namespace RoundTarget_test

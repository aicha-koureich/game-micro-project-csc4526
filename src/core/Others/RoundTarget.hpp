#ifndef SIMPLE_GAME_ROUND_TARGET_H
#define SIMPLE_GAME_ROUND_TARGET_H

#include <SFML/Graphics.hpp>

static constexpr auto nbFramesWhenDying{60};

enum class RoundTargetStatus {
  Alive,  ///< Target is moving around screen
  Dying,  ///< Target has been hit by mouse and is playing animation before
          ///< getting dead
  Dead    ///< Target is dead (its dying animation is over).
};

class RoundTarget {
 public:
  RoundTarget(float radius, sf::Color color, float x, float y, float speedX,
              float speedY);
  void die();
  void drawCurrent(sf::RenderWindow &window) const;
  const sf::CircleShape &getShape() const;
  bool isDead() const;
  bool isHitByMouse(const sf::Vector2i &mousePosition) const;
  void update(const sf::Time &elapsedTime, const sf::Vector2u &windowSize);

 private:
  int mNbFramesBeforeDeath{std::numeric_limits<int>::max()};
  float mOriginalRadius;
  sf::CircleShape mShape;
  sf::Vector2f mSpeed;
  RoundTargetStatus mStatus{RoundTargetStatus::Alive};
};

#endif  // SIMPLE_GAME_ROUND_TARGET_H

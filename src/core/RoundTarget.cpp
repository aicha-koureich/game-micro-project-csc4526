#include "RoundTarget.hpp"

RoundTarget::RoundTarget(const float radius, const sf::Color color,
                         const float x, const float y, const float speedX,
                         const float speedY)
    : mOriginalRadius{radius} {
  mShape.setRadius(radius);
  mShape.setFillColor(color);
  mShape.setPosition({x, y});
  mSpeed.x = speedX;
  mSpeed.y = speedY;
}

void RoundTarget::die() {
  mStatus = RoundTargetStatus::Dying;
  mNbFramesBeforeDeath = nbFramesWhenDying;
  mShape.setFillColor(sf::Color::Red);
  mSpeed.x = 0;
  mSpeed.y = 0;
}

void RoundTarget::drawCurrent(sf::RenderWindow &window) const {
  window.draw(mShape);
}

const sf::CircleShape &RoundTarget::getShape() const { return mShape; }

bool RoundTarget::isDead() const { return mStatus == RoundTargetStatus::Dead; }

bool RoundTarget::isHitByMouse(const sf::Vector2i &mousePosition) const {
  sf::Vector2f mouseFloatPosition{static_cast<float>(mousePosition.x),
                                  static_cast<float>(mousePosition.y)};
  sf::Vector2f centerRelativePosition{mShape.getRadius(), mShape.getRadius()};
  auto distanceVec =
      mShape.getPosition() + centerRelativePosition - mouseFloatPosition;
  return distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y <
         mShape.getRadius() * mShape.getRadius();
}

void RoundTarget::update(const sf::Time &elapsedTime,
                         const sf::Vector2u &windowSize) {
  switch (mStatus) {
    case RoundTargetStatus::Alive:
      mShape.move(mSpeed * elapsedTime.asSeconds());
      if (mShape.getPosition().x < 0) {
        // Shape has bounced on left border of screen
        mShape.setPosition({-mShape.getPosition().x, mShape.getPosition().y});
        mSpeed.x = -mSpeed.x;
      }
      if (mShape.getPosition().y < 0) {
        // Shape has bounced on upper border of screen
        mShape.setPosition({mShape.getPosition().x, -mShape.getPosition().y});
        mSpeed.y = -mSpeed.y;
      }
      if (mShape.getPosition().x + 2 * mShape.getRadius() >
          static_cast<float>(windowSize.x)) {
        // Shape has bounced on right border of screen
        mShape.setPosition({2 * static_cast<float>(windowSize.x) -
                                4 * mShape.getRadius() - mShape.getPosition().x,
                            mShape.getPosition().y});
        mSpeed.x = -mSpeed.x;
      }
      if (mShape.getPosition().y + 2 * mShape.getRadius() >
          static_cast<float>(windowSize.y)) {
        // Shape has bounced on right border of screen
        mShape.setPosition(
            {mShape.getPosition().x, 2 * static_cast<float>(windowSize.y) -
                                         4 * mShape.getRadius() -
                                         mShape.getPosition().y});
        mSpeed.y = -mSpeed.y;
      }
      break;
    case RoundTargetStatus::Dying:
      mShape.setRadius(mOriginalRadius *
                       static_cast<float>(mNbFramesBeforeDeath) /
                       nbFramesWhenDying);
      mShape.move({1.f / nbFramesWhenDying, 1.f / nbFramesWhenDying});
      --mNbFramesBeforeDeath;
      if (mNbFramesBeforeDeath == 0) {
        mStatus = RoundTargetStatus::Dead;
      }
      break;
    case RoundTargetStatus::Dead:
      break;
  }
}

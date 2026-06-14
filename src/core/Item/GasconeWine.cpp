#include "GasconeWine.hpp"

#include "Entities/Player.hpp"

GasconeWine::GasconeWine(int cost, float effect) : Item(cost, effect) {}

// heal le player
bool GasconeWine::used(Player& player) {
  float hp = (float)player.getHealthPoints();
  if (hp == MAX_HEALTH_POINTS) return false;
  float buffedHp = hp * (1 + effect);

  if ((buffedHp) > MAX_HEALTH_POINTS) {
    buffedHp = MAX_HEALTH_POINTS;
  }
  player.setHealthPoints(buffedHp);
  return true;
}

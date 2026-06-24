#include "GasconeWine.hpp"

#include "Entities/Player.hpp"

GasconeWine::GasconeWine(int cost, float effect) : Item(cost, effect) {}

// heal le player
bool GasconeWine::used(Player& player) {
  int hp = player.getHealthPoints();
  int maxHp = player.getMaxHealthPoints();
  if (hp == maxHp) return false;

  int boost = std::max(1, static_cast<int>(maxHp * effect));
  float buffedHp = hp + boost;

  if ((buffedHp) > maxHp) {
    buffedHp = maxHp;
  }
  player.setHealthPoints(buffedHp);
  return true;
}
std::unique_ptr<Item> GasconeWine::clone() const {
    return std::make_unique<GasconeWine>(*this); 
}
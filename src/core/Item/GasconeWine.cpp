#include "GasconeWine.hpp"

#include "Entities/Player.hpp"

GasconeWine::GasconeWine(int cost, float effect) : Item(cost, effect) {}

// heal le player
bool GasconeWine::used(Player& player) {
  float hp = (float)player.getHealthPoints();
  if (hp == player.getMaxHealthPoints()) return false;
  float buffedHp = hp * (1 + effect);

  if ((buffedHp) > player.getMaxHealthPoints()) {
    buffedHp = player.getMaxHealthPoints();
  }
  player.setHealthPoints(buffedHp);
  return true;
}
std::unique_ptr<Item> GasconeWine::clone() const {
    return std::make_unique<GasconeWine>(*this); 
}
#include "InkFlask.hpp"

#include "Entities/Player.hpp"

InkFlask::InkFlask(int cost, float effect) : Item(cost, effect) {}

// Booste le multiplicateur d'eloquence du joueur (independant de l'arme
// equipee)
bool InkFlask::used(Player& player) {
  float currentMultiplier = player.getEloquenceMultiplier();
  float buffedMultiplier = currentMultiplier + effect;

  player.setEloquenceMultiplier(buffedMultiplier);
  return true;
}

std::unique_ptr<Item> InkFlask::clone() const {
  return std::make_unique<InkFlask>(*this);
}
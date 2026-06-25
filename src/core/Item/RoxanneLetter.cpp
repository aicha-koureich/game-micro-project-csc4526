#include "RoxanneLetter.hpp"

#include "Entities/Player.hpp"

using namespace std;

RoxanneLetter::RoxanneLetter(int cost, float effect) : Item(cost, effect) {}

// Booste le multiplicateur de force du joueur (independant de l'arme
// equipee)
bool RoxanneLetter::used(Player& player) {
  float currentMultiplier = player.getStrengthMultiplier();
  float buffedMultiplier = currentMultiplier + effect;

  player.setStrengthMultiplier(buffedMultiplier);
  return true;
}

std::unique_ptr<Item> RoxanneLetter::clone() const {
  return std::make_unique<RoxanneLetter>(*this);
}
#include "RoxanneLetter.hpp"
#include "Entities/Player.hpp"

using namespace std;

RoxanneLetter::RoxanneLetter(int cost, float effect) : Item(cost, effect) {}

bool RoxanneLetter::used(Player& player) {
  Weapon* activeWeapon = player.getCurrentWeapon();

  // Sécurité : on vérifie qu'une arme est bien équipée et que c'est une épée
  // (Strength)
  if (activeWeapon == nullptr ||
      activeWeapon->getType() != AttackType::STRENGTH) {
    std::cout << "No strength weapon equipped to boost!\n";
    return false;
  }

  int weaponEff = activeWeapon->getEffect();
  if (weaponEff >= MAX_WEAPON_EFFECT) {
    std::cout << "Weapon already at max effect!\n";
    return false;
  }

  int boost = std::max(1, static_cast<int>(weaponEff * effect));
  int buffedWeaponEff = weaponEff + boost;

  if (buffedWeaponEff > MAX_WEAPON_EFFECT) {
    buffedWeaponEff = MAX_WEAPON_EFFECT;
  }

  activeWeapon->setEffect(buffedWeaponEff);
  return true;
}

std::unique_ptr<Item> RoxanneLetter::clone() const {
    return std::make_unique<RoxanneLetter>(*this); 
}
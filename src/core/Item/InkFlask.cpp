#include "InkFlask.hpp"

#include "Entities/Player.hpp"

InkFlask::InkFlask(int cost, float effect) : Item(cost, effect) {}

bool InkFlask::used(Player& player) {
  Weapon* activeWeapon = player.getCurrentWeapon();

  // Sécurité : on vérifie qu'une arme est bien équipée et que c'est une plume
  // (Eloquence)
  if (activeWeapon == nullptr ||
      activeWeapon->getType() != AttackType::ELOQUENCE) {
    std::cout << "No eloquence weapon equipped to boost!\n";
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

std::unique_ptr<Item> InkFlask::clone() const {
    return std::make_unique<InkFlask>(*this); 
}
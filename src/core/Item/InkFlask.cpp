#include "InkFlask.hpp"

#include "Entities/Player.hpp"

InkFlask::InkFlask(int cost, float effect) : Item(cost, effect) {}

bool InkFlask::used(Player& player) {
  Weapon* weapon = player.getCurrentWeapon();
  if(weapon == nullptr) return false;
  if (weapon->getType() == AttackType::ELOQUENCE) {
    int weaponEff = weapon->getEffect();
    if (weaponEff == MAX_WEAPON_EFFECT) return false;
    
    int buffedWeaponEff = weaponEff * (1 + effect);
    if (buffedWeaponEff > MAX_WEAPON_EFFECT) {
      buffedWeaponEff = MAX_WEAPON_EFFECT;
    }
    weapon->setEffect(buffedWeaponEff);
    return true;
  }
  else{ //currentWeapon == SWORD
    return false;
  }
}

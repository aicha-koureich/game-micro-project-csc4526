#include "RoxanneLetter.hpp"
#include "Entities/Player.hpp"

RoxanneLetter::RoxanneLetter(int cost, float effect) : Item(cost, effect) {}

bool RoxanneLetter::used(Player& player) {
  Weapon* weapon = player.getCurrentWeapon();
  if(weapon == nullptr) return false;
  if (weapon->getType() == WeaponType::SWORD) {
    int weaponEff = weapon->getEffect();
    if (weaponEff == MAX_WEAPON_EFFECT) return false;
    
    int buffedWeaponEff = weaponEff * (1 + effect);
    if (buffedWeaponEff > MAX_WEAPON_EFFECT) {
      buffedWeaponEff = MAX_WEAPON_EFFECT;
    }
    weapon->setEffect(buffedWeaponEff);
    return true;
  }
  else{ //currentWeapon == FEATHER
    return false;
  }
}

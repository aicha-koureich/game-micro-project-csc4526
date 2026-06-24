#include "RoxanneLetter.hpp"
#include "Entities/Player.hpp"

RoxanneLetter::RoxanneLetter(int cost, float effect) : Item(cost, effect) {}

bool RoxanneLetter::used(Player& player) {
  bool success = false;
  for(auto& weapon : player.getWeaponInventory()){
    if (weapon->getType() == AttackType::STRENGTH) {
      int weaponEff = weapon->getEffect();
      if (weaponEff == MAX_WEAPON_EFFECT) continue;
      
      int boost = std::max(1, static_cast<int>(weaponEff * effect));
      int buffedWeaponEff = weaponEff + boost;
      if (buffedWeaponEff > MAX_WEAPON_EFFECT) {
        buffedWeaponEff = MAX_WEAPON_EFFECT;
      }
      weapon->setEffect(buffedWeaponEff);
      success =true;
    }
  }
  return success;
}

std::unique_ptr<Item> RoxanneLetter::clone() const {
    return std::make_unique<RoxanneLetter>(*this); 
}
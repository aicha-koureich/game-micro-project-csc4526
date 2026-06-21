#include "Sword.h"

bool Sword::registered = Factory::register_class_name(
    "Sword", [](pugi::xml_node const& node) -> std::unique_ptr<Weapon> {
      int damage = node.attribute("effect").as_int();
      std::string name = node.attribute("name").as_string();
      int cost = node.attribute("cost").as_int();
      return std::make_unique<Sword>(damage, name, cost);
    });

Sword::Sword(int damage, std::string swordName, int swordCost) : Weapon(damage, swordName, swordCost, AttackType::STRENGTH) {}

void Sword::attack(Enemy& target, float performance) {
  int damageToApply = std::round(effect * performance);
  target.takeDamage(damageToApply);
}
#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"
#include "Factories/Factory.h"

class Sword : public Weapon {
 private:
  static inline bool registered = Factory::register_class_name(
      "Sword", [](pugi::xml_node const& node) -> std::unique_ptr<Weapon> {
        int damage = node.attribute("effect").as_int();
        std::string name = node.attribute("name").as_string();
        int cost = node.attribute("cost").as_int();
        return std::make_unique<Sword>(damage, name, cost);
      });

	public:
        Sword(int damage, std::string swordName, int swordCost);
        void attack(Enemy& target, float performance) override;
};

#endif
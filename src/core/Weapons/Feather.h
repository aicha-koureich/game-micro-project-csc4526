#ifndef FEATHER_H
#define FEATHER_H

#include "Factories/Factory.h"
#include "Weapon.h"

enum class DebuffType { STRENGTH, DEFENSE };

class Feather : public Weapon {
 private:
  DebuffType currentChoice;
  static inline bool registered = Factory::register_class_name(
      "Feather", [](pugi::xml_node const& node) -> std::unique_ptr<Weapon> {
        int power = node.attribute("effect").as_int();
        std::string name = node.attribute("name").as_string();
        int cost = node.attribute("cost").as_int();
        return std::make_unique<Feather>(power, name, cost);
      });

 public:
  Feather(int eloquencePower, std::string featherName, int featherCost);
  void attack(Enemy& target, float performance) override;
  void setDebuffChoice(DebuffType choice);
};

#endif
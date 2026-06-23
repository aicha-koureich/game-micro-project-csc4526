#ifndef FEATHER_H
#define FEATHER_H

#include "Factories/Factory.h"
#include "Weapon.h"

enum class DebuffType { STRENGTH, DEFENSE };

class Feather : public Weapon {
 private:
  DebuffType currentChoice;
  static bool registered;

 public:
  Feather(int eloquencePower, std::string featherName, int featherCost);
  void attack(Enemy& target, float performance) override;
  void setDebuffChoice(DebuffType choice);
};

#endif
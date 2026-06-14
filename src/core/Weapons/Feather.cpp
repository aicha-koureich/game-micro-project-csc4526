#include "Feather.h"
#include "Entity.hpp"
#include <iostream>
using namespace std;

Feather::Feather(int power, std::string name, int cost) : Weapon(power, name, cost, AttackType::ELOQUENCE), currentChoice(DebuffType::STRENGTH) {}

void Feather::setDebuffChoice(DebuffType choice) { 
	currentChoice = choice;
}

int Feather::attack(Entity& target, float performance) {
  int calculatedEffect = effect * performance;

  if (currentChoice == DebuffType::STRENGTH) {
    target.reduceStrength(calculatedEffect);
  } else if (currentChoice == DebuffType::DEFENSE) {
    target.reduceDefense(calculatedEffect);
  }

}
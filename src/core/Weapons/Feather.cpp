#include "Feather.h"
#include <iostream>
using namespace std;

bool Feather::registered = Factory::register_class_name(
    "Feather", [](pugi::xml_node const& node) -> std::unique_ptr<Weapon> {
    int power = node.attribute("effect").as_int();
    std::string name = node.attribute("name").as_string();
    int cost = node.attribute("cost").as_int();
    return std::make_unique<Feather>(power, name, cost);
    });


Feather::Feather(int power, std::string name, int cost) : Weapon(power, name, cost, AttackType::ELOQUENCE), currentChoice(DebuffType::STRENGTH) {}

void Feather::setDebuffChoice(DebuffType choice) { 
	currentChoice = choice;
}

void Feather::attack(Enemy& target, float performance, float playerMult) {
  int calculatedEffect = std::round(effect * performance);

  if (currentChoice == DebuffType::STRENGTH) {
    target.reduceStrength(calculatedEffect);
  } else if (currentChoice == DebuffType::DEFENSE) {
    target.reduceDefense(calculatedEffect);
  } else {
    std::cout << "Aucun debuff sélectionné ou debuff invalide\n";
  }

}
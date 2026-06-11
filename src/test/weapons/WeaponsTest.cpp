#include <iostream>
#include <cassert>
#include <memory>
#include "Factories/Factory.h"
#include "Weapons/Weapon.h"

void testStrengthFactory() {
  std::unique_ptr<Factory> factory = std::make_unique<StrengthFactory>();

  std::unique_ptr<Weapon> weapon = factory->createWeapon(15);
  assert(weapon != nullptr && "Erreur : L'arme créée est un pointeur nul");

  assert(weapon->getEffect() == 15 && "Erreur : Dégâts de Sword incorrects");

  assert(weapon->getType() == AttackType::Force &&
         "Erreur : Type d'attaque de Sword incorrect");

  std::cout << "Test StrengthFactory validé" << std::endl;

}

void testEloquenceFactory() {
  std::unique_ptr<Factory> factory = std::make_unique<EloquenceFactory>();

  std::unique_ptr<Weapon> weapon = factory->createWeapon(30);
  assert(weapon != nullptr && "Erreur : L'arme créée est un pointeur nul");

  assert(weapon->getEffect() == 30 && "Erreur : Puissance de Feather incorrect");

  assert(weapon->getType() == AttackType::Eloquence &&
         "Erreur : Type d'attaque de Feather incorrect");

  std::cout << "Test EloquenceFactory validé" << std::endl;
}

int main() {
    testStrengthFactory();
    testEloquenceFactory();

    return 0;
}


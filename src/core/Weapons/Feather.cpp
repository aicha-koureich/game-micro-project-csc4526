#include "Feather.h"
#include <iostream>
using namespace std;

Feather::Feather(int power, std::string name, int cost) : Weapon(power, name, cost, AttackType::ELOQUENCE) {}

int Feather::reduceEnemyStrength(Entity& other) { return 1; }

int Feather::reduceEnemyDefense(Entity& other) { return 2; }


int Feather::attack(Entity& target, float performance) {
	//si le player choisit reduceEnemyDamage:
    reduceEnemyStrength(target);

	//si le joueur choisit reduceEnemyDefense
    reduceEnemyDefense(target);
}
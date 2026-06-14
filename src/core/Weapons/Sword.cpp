#include "Sword.h"
#include <iostream>
using namespace std;

Sword::Sword(WeaponType type, const std::string& name, int weaponEffect, int cost) : Weapon(type, name, weaponEffect, cost) {}

int attack(Entity& entity){
    cout<<"sword attacks entity\n";
    return 0;
}
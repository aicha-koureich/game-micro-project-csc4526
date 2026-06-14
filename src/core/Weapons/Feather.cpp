#include "Feather.h"
#include <iostream>
using namespace std;

Feather::Feather(WeaponType type, const std::string& name, int weaponEffect, int cost):Weapon(type, name, weaponEffect, cost){}

int attack(Entity& entity){
    cout<<"feather attacks entity\n";
    return 0;
}
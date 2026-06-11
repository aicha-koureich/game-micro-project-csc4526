#include "Enemy.hpp"
//#include "Weapons/Weapon.h"

Enemy::Enemy(int healthPoints) { 
	this.healthPoints = healthPoints; 
}

AttackType Enemy::getSensitivity() { return sensitivity; }

void Enemy::takeDamage(int attackRes) {
	target.healthPoints -= attackRes;
}

void Enemy::attack(const Entity& target, AttackType type) {

}


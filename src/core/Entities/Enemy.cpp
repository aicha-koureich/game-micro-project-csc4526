#include "Enemy.hpp"
//#include "Weapons/Weapon.h"

Enemy::Enemy(int healthPoints) { 
	this.healthPoints = healthPoints; 
}

AttackType Enemy::getSensitivity() { return sensitivity; }

void Enemy::takeDamage(Entity& target, int attackRes) {
	target.healthPoints -= attackRes;

	if (target.healthPoints <= 0) {
		target.Die();
    }

}

void Enemy::attack(Entity& attacker, AttackType type) {

}


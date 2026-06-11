#include "Enemy.hpp"
//#include "Weapons/Weapon.h"

Enemy::Enemy(int hp) : Entity(hp), sensitivity(AttackType::STRENGTH), enemyDamage(50){ 
}

AttackType Enemy::getSensitivity() const{ return sensitivity; }

void Enemy::takeDamage(int attackRes) {
}

void Enemy::attack(const Entity& target, AttackType type) {

}


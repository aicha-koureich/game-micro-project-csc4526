#include "Enemy.hpp"
#include "Weapons/Weapon.h"

Enemy::Enemy(int hp) : Entity(hp){}


void Enemy::receiveAttack(int trueDamage, AttackType) {

}

int Enemy::attack(const Entity& target) {}


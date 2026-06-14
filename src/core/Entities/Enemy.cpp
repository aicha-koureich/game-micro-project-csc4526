#include "Enemy.hpp"
#include "Weapons/Weapon.h"
#include <cmath>

Enemy::Enemy(int hp, float sensitivity, int damage, int defense, int level) : Entity(hp), sensitivityToEloq(sensitivity), enemyDamage(damage), enemyDefense(defense), enemyLevel(level){}

void Enemy::reduceStrength(int amount) {
  int reduction = (amount * sensitivityToEloq) / enemyLevel;
  enemyDamage = std::max(1, enemyDamage - reduction);

}

int Enemy::reduceDefense(int amount) {
  int reduction = (amount * sensitivityToEloq) / enemyLevel;
  enemyDefense = std::max(0, enemyDefense - reduction);

}

void Enemy::receiveAttack(int attackRes) {


}


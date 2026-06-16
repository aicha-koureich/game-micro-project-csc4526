#include "Enemy.hpp"
#include <iostream>
#include <cmath>

Enemy::Enemy(int hp, float sensitivity, int damage, int defense, int level) : Entity(hp), sensitivityToEloq(sensitivity), baseDamage(damage), currentDamage(damage), baseDefense(defense), currentDefense(defense), enemyLevel(level){}

void Enemy::reduceStrength(int amount) {
  int reduction = (amount * sensitivityToEloq) / enemyLevel;
  currentDamage = std::max(1, currentDamage - reduction);

  std::cout << "Attaque de l'ennemi réduite ! Actuelle : " << currentDamage
            << "\n";

}

void Enemy::reduceDefense(int amount) {
  int reduction = (amount * sensitivityToEloq) / enemyLevel;
  currentDefense = std::max(0, currentDefense - reduction);

  std::cout << "Défense de l'ennemi réduite ! Actuelle : " << currentDefense
            << "\n";
}

void Enemy::takeDamage(int attackRes) {
  int finalDamage = std::max(1, attackRes - currentDefense);
  healthPoints = std::max(0, healthPoints - finalDamage);

  std::cout << "L'ennemi subit " << finalDamage << " PV. PV restants : " << healthPoints
            << "\n";

}

void Enemy::resetTurnDebuffs() { 
    currentDamage = baseDamage;
    currentDefense = baseDefense;
}

void Enemy::enemyAttack(Entity& target) { target.takeDamage(currentDamage); }


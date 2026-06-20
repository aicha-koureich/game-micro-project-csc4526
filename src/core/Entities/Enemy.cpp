#include "Enemy.hpp"
#include <iostream>
#include <cmath>

Enemy::Enemy(int maxHp, float sensitivity, int damage, int defense, int level) : Entity(maxHp), sensitivityToEloq(sensitivity), baseDamage(damage), currentDamage(damage), baseDefense(defense), currentDefense(defense), enemyLevel(level){}


void Enemy::takeDamage(int attackRes) {
  int finalDamage = std::max(1, attackRes - currentDefense);
  healthPoints = std::max(0, healthPoints - finalDamage);

  std::cout << "L'ennemi subit " << finalDamage << " PV. PV restants : " << healthPoints
            << "\n";

}

void Enemy::enemyAttack(Entity& target, float playerPerf) {
  target.takeDamage(currentDamage / playerPerf);
}

void Enemy::reduceStrength(int amount) {
  int reduction = (amount * sensitivityToEloq) / enemyLevel;
  currentDamage = std::max(1, currentDamage - reduction);
  attackDebuffActive = true;

  std::cout << "Attaque de l'ennemi réduite ! Actuelle : " << currentDamage
            << "\n";
}

void Enemy::reduceDefense(int amount) {
  int reduction = (amount * sensitivityToEloq) / enemyLevel;
  currentDefense = std::max(0, currentDefense - reduction);
  defenseDebuffActive = true;

  std::cout << "Défense de l'ennemi réduite ! Actuelle : " << currentDefense
            << "\n";
}

void Enemy::resetAttackDebuff() { 
    if (attackDebuffActive) {
        currentDamage = baseDamage;
        attackDebuffActive = false;
  
    }
     
}

void Enemy::resetDefenseDebuff() {
  if (defenseDebuffActive) {
    currentDefense = baseDefense;
    defenseDebuffActive = false;
  }
}




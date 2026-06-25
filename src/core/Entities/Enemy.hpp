#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

class Enemy : public Entity {
 private:
  float sensitivityToEloq;
  int enemyLevel;

  int baseDamage;
  int currentDamage;
  int baseDefense;
  int currentDefense;
  


 public:
  Enemy(int maxHp, float sensitivity, int damage, int defense, int level);
  ~Enemy() override = default;

  float getSensitivityToEloq() const { return sensitivityToEloq;}
  int getCurrentDamage() const { return currentDamage; }
  int getCurrentDefense() const { return currentDefense; }
  int getEnemyLevel() const { return enemyLevel; }

  void takeDamage(int attackRes) override;
  void enemyAttack(Entity& target, float playerPerf);
  void reduceStrength(int amount);
  void reduceDefense(int amount);

  //Debuffs
  bool attackDebuffActive{false};
  bool defenseDebuffActive{false};
  void resetAttackDebuff();
  void resetDefenseDebuff();
  
};
#endif
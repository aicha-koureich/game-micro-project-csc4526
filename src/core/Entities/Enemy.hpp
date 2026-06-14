#include "AttackType.hpp"
#include "Entity.hpp"

class Enemy : public Entity {
 private:
  float sensitivityToEloq;
  int enemyDamage;
  int enemyDefense;
  int enemyLevel;


 public:
  Enemy(int hp, float sensitivity, int damage, int level);
  ~Enemy() override = default;
  float getSensitivityToEloq() const { return sensitivityToEloq;}

  void receiveAttack(int attackRes) override;
  void reduceStrength(int amount) override;
  void reduceDefense(int amount) override;
};
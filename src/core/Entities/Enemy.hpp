#include "AttackType.hpp"
#include "Entity.hpp"

class Enemy : public Entity {
 private:
  float sensitivityToEloq;
  int enemyDamage;
  int enemyLevel;

 public:
  Enemy(int hp);
  ~Enemy() override = default;
  float getSensitivityToEloq() const { return sensitivityToEloq;}
  void takeDamage(int attackRes) override;
  int attack(const Entity& target) override;
};
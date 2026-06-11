#include "AttackType.hpp"
#include "Entity.hpp"

class Player : public Entity {
 private:
//Manque tout ce qui concerne Weapon et Items et increaseNoseSize()
  AttackType currentAttack;
  int baseDamage;
  int baseDefense;
  int noseSize;
  float speed;
  bool isBlocking;
  

 public:
  void takeDamage(const Entity& attacker, AttackType type) override;
  void attack(const Entity& target, AttackType type) override;
  AttackType chooseAttackType();
  AttackType getCurrentAttackType();
  Player(int hp);
  ~Player() override = default;
};

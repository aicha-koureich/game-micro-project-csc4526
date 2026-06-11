#include "AttackType.hpp"
#include "Entity.hpp"

class Enemy : public Entity {
 private:
  const AttackType sensitivity;
  int enemyDamage;
  // std::pair < std::unique_ptr<Weapon>, std::unique_ptr<Weapon>>

 public:
  Enemy(int hp);
  ~Enemy() override = default;
  AttackType getSensitivity() const;
  void takeDamage(int attackRes) override;
  void attack(const Entity& target, AttackType type) override;
  // std::pair < std::unique_ptr<Weapon>, std::unique_ptr<Weapon>>
  // dropWeapons();
};
#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity {
 protected:
  int healthPoints{0};
  int maxHealthPoints{100};

 public:

  virtual void takeDamage(int attackRes) = 0;
  Entity(int maxHp) : healthPoints(maxHp), maxHealthPoints(maxHp) {}
  virtual ~Entity() = default;
  int getHealthPoints() const { return healthPoints; }
  int getMaxHealthPoints() const { return maxHealthPoints; }
};

#endif



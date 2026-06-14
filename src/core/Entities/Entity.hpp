#ifndef ENTITY_HPP
#define ENTITY_HPP

#define MAX_HEALTH_POINTS 100

class Entity {
 protected:
  int healthPoints;

 public:

  virtual void takeDamage(int attackRes) = 0;
  virtual int attack(const Entity& target) = 0;
  Entity(int hp) : healthPoints(hp) {}
  virtual ~Entity() = default;
  int getHealthPoints() const { return healthPoints; }
  void setHealthPoints(int hp) {healthPoints = hp;}
};

#endif


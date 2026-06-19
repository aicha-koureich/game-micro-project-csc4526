#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity {
 protected:
  int healthPoints;

 public:

  virtual void takeDamage(int attackRes) = 0;
  Entity(int hp) : healthPoints(hp) {}
  virtual ~Entity() = default;
  int getHealthPoints() const { return healthPoints; }
};

#endif



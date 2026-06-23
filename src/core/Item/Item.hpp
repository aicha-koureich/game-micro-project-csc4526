#ifndef ITEM_HPP
#define ITEM_HPP

class Player; // juste pour quil sache que player existe
class Item {
 protected:
  int cost;
  float effect;

 public:
  Item(int c, float e) : cost(c), effect(e) {}
  virtual ~Item() = default;
  virtual bool used(Player& player) = 0;
  int getCost() const{ return cost; }
};
#endif
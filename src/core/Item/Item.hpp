#ifndef ITEM_HPP
#define ITEM_HPP

class Player; // juste pour quil sache que player existe si je fais un include le compilo va vriller parce que j'include item dans player aussi

class Item {
 protected:
  int cost;
  float effect;

 public:
  Item(int c, float e) : cost(c), effect(e) {}
  virtual ~Item() = default;
  virtual bool used(Player& player) = 0;
};
#endif
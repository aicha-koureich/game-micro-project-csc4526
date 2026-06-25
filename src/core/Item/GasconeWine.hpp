#ifndef GASCONEWINE_HPP
#define GASCONEWINE_HPP

#include "Item.hpp"

class GasconeWine : public Item {
 public:
  GasconeWine(int cost, float effect);
  ~GasconeWine() = default;
  bool used(Player& player) override;
  std::unique_ptr<Item> clone() const override;
};

#endif
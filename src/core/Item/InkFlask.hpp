#ifndef INK_FLASK
#define INK_FLASK

#include "Item.hpp"

class InkFlask : public Item {
 public:
  InkFlask(int cost, float effect);
  ~InkFlask() = default;
  bool used(Player& player) override;
  std::unique_ptr<Item> clone() const override;
};

#endif
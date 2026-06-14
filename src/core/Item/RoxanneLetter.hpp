#ifndef ROXANNE_LETTER
#define ROXANNE_LETTER

#include "Item.hpp"

class RoxanneLetter : public Item {
 public:
  RoxanneLetter(int cost, float effect);
  ~RoxanneLetter() = default;
  bool used(Player& player) override;
};

#endif
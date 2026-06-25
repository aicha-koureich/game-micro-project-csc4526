#include <gtest/gtest.h>

#include "Entities/Enemy.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Player.hpp"
#include "Factories/Factory.h"
#include "Item/GasconeWine.hpp"
#include "Item/InkFlask.hpp"
#include "Item/RoxanneLetter.hpp"
#include "Weapons/Feather.h"
#include "Weapons/Sword.h"

namespace Item_test {

TEST(ItemTest, gasconeWineRestoresHealth) {
  // maxHp, money, size, maxMana, defense, currentWeapon
  Player player{100, 0, 10.f, 50, 5, nullptr};
  player.restoreHealth();
  GasconeWine wine{5, 0.5f};

  player.setHealthPoints(50);
  wine.used(player);

  EXPECT_EQ(player.getHealthPoints(), 100);
}

TEST(ItemTest, inkFlaskBoostsEloquenceMultiplier) {
  Player player{100, 500, 10.f, 50, 5, nullptr};
  InkFlask ink{10, 0.25f};

  ink.used(player);

  EXPECT_FLOAT_EQ(player.getEloquenceMultiplier(), 1.25f);
}

TEST(ItemTest, roxanneLetterBoostsStrengthMultiplier) {
  Player player{100, 500, 10.f, 50, 5, nullptr};
  RoxanneLetter letter{15, 0.25f};

  letter.used(player);

  EXPECT_FLOAT_EQ(player.getStrengthMultiplier(), 1.25f);
}

}  // namespace Item_test
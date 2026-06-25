#include <gtest/gtest.h>

#include "Entities/Entity.hpp"
#include "Entities/Player.hpp"
#include "Item/GasconeWine.hpp"
#include "Item/InkFlask.hpp"
#include "Item/Item.hpp"
#include "Item/RoxanneLetter.hpp"
#include "Weapons/Feather.h"
#include "Weapons/Sword.h"

namespace Item_test {

// Petite classe concrete minimale pour tester le contrat de la classe
// abstraite Item en isolation, sans dependre de la logique d'un item reel.
class MockItem : public Item {
 public:
  bool usedCalled = false;

  MockItem(int c, float e) : Item(c, e) {}

  bool used(Player& player) override {
    usedCalled = true;
    (void)player;
    return true;
  }

  std::unique_ptr<Item> clone() const override {
    return std::make_unique<MockItem>(*this);
  }
};

TEST(ItemTest, constructorStoresCost) {
  MockItem item{42, 0.5f};

  EXPECT_EQ(item.getCost(), 42);
}

TEST(ItemTest, getCostIsConstAndStable) {
  const MockItem item{7, 0.1f};

  EXPECT_EQ(item.getCost(), 7);
  EXPECT_EQ(item.getCost(), 7);
}

TEST(ItemTest, cloneReturnsNonNullItem) {
  MockItem item{10, 0.3f};

  std::unique_ptr<Item> clone = item.clone();

  ASSERT_NE(clone, nullptr);
}

TEST(ItemTest, clonePreservesCost) {
  MockItem item{25, 0.2f};

  std::unique_ptr<Item> clone = item.clone();

  EXPECT_EQ(clone->getCost(), item.getCost());
}

TEST(ItemTest, cloneReturnsIndependentInstance) {
  MockItem item{5, 0.5f};

  std::unique_ptr<Item> clone = item.clone();

  // l'original et le clone doivent etre deux objets distincts en memoire
  EXPECT_NE(clone.get(), static_cast<Item*>(&item));
}

TEST(ItemTest, usedIsDispatchedPolymorphicallyThroughBasePointer) {
  Player player{100, 0, 10.f, 50, 5, nullptr};
  std::unique_ptr<Item> item = std::make_unique<MockItem>(1, 0.1f);

  bool result = item->used(player);

  EXPECT_TRUE(result);
  EXPECT_TRUE(static_cast<MockItem*>(item.get())->usedCalled);
}

// Les tests suivants verifient que des items reels du projet respectent bien
// le contrat de la classe Item (cost expose, used()/clone() polymorphiques)
// quand ils sont manipules via un pointeur de base Item*.

TEST(ItemTest, realItemExposesCostThroughBaseClass) {
  std::unique_ptr<Item> wine = std::make_unique<GasconeWine>(5, 0.5f);

  EXPECT_EQ(wine->getCost(), 5);
}

TEST(ItemTest, realItemCloneKeepsDynamicType) {
  std::unique_ptr<Item> ink = std::make_unique<InkFlask>(10, 0.25f);

  std::unique_ptr<Item> clone = ink->clone();

  EXPECT_NE(dynamic_cast<InkFlask*>(clone.get()), nullptr);
}

TEST(ItemTest, realItemUsedCallableThroughBasePointer) {
  Player player{100, 0, 10.f, 50, 5, nullptr};
  player.restoreHealth();
  player.setHealthPoints(50);
  std::unique_ptr<Item> wine = std::make_unique<GasconeWine>(5, 0.5f);

  bool result = wine->used(player);

  EXPECT_TRUE(result);
  EXPECT_EQ(player.getHealthPoints(), 100);
}

}  // namespace Item_test
#include <gtest/gtest.h>

#include "Entities/Entity.hpp"
#include "Entities/Player.hpp"
#include "Entities/Enemy.hpp"
#include "Weapons/Sword.h"
#include "Weapons/Feather.h"
#include "Factories/Factory.h"

namespace Player_test {
// Test de l'épée avec calcul des dégâts et de la performance
TEST(increaseNoseSize, noseSize_increasesAfterAFight) {

  Sword sword{10, "Excalibur", 100};
  Player player{100, 50, 10.f, 5, &sword};
  
  player.increaseNoseSize(0);

  EXPECT_FLOAT_EQ(player.getNoseSize(), 20.f);
}

TEST(takeDamage, player_takeDamage) { 
	Sword sword{10, "Excalibur", 100};
    Enemy enemy{100, 2.0f, 10, 20, 2};  //Ennemi qui fait 10 de dégâts
    Player player{100, 50, 10.f, 5, &sword};    //Player avec 5 points de défense 

    enemy.enemyAttack(player, 0.f); //Ennemi inflige 10 - 5 = 5 dégats

    EXPECT_EQ(player.getHealthPoints(), 95);

}

TEST(takeDamage, enemyDamageTooLow) {
  Sword sword{10, "Excalibur", 100};  // Epée infligeant 10 points de dégats
  Enemy enemy{100, 2.0f, 10, 5, 2};   // Ennemi avec 10 points de dégâts
  Player player{100, 50, 10.f, 15, &sword};  // Player avec 15 points de défense

  enemy.enemyAttack(player, 0.f);  // Ennemi inflige 10 - 15 = -5 donc son attaque va
                              // faire 1 point de dégâts

  EXPECT_EQ(player.getHealthPoints(), 99);
}

TEST(takeDamage, enemyKillPlayer) {
  Sword sword{10, "Excalibur", 100};  // Epée infligeant 10 points de dégats
  Enemy enemy{100, 2.0f, 200, 5,
              2};  // Ennemi qui avec 100 hp et 5 points de défense
  Player player{100, 50, 10.f, 15, &sword};  // Player avec 15 points de défense

  enemy.enemyAttack(player, 0.f);  // Ennemi inflige 10 - 15 = -5 donc son attaque va
                              // faire 1 point de dégâts

  EXPECT_EQ(player.getHealthPoints(), 0);
}

TEST(playerAttack, player_attacksAnEnemy) {
  Sword sword{10, "Excalibur", 100};        //Epée infligeant 10 points de dégats
  Enemy enemy{100, 2.0f, 10, 5, 2};        // Ennemi qui avec 100 hp et 5 points de défense
  Player player{100, 50, 10.f, 5, &sword};  // Player avec 5 points de défense

  player.playerAttack(enemy, 1.5f);  //Player inflige 10*1.5 = 15 points de dégats

  EXPECT_EQ(enemy.getHealthPoints(), 90);

}

TEST(pickWeapon, player_withoutWeaponTakesAFeatherFromInventory) {
    Player player{100, 500, 10.f, 5, nullptr};  //Player avec 500 pièces et sans arme
  std::unique_ptr<Weapon> feather =
      std::make_unique<Feather>(20, "Goose Feather", 150);

  player.purchaseWeapon(std::move(feather));
  EXPECT_EQ(player.getTotalMoney(), 350);

  player.pickWeapon(0);
  EXPECT_EQ(player.getCurrentWeapon(), player.getWeaponInventory()[0].get());

}


TEST(pickWeapon, player_takesAWeaponInInventoryThenOutOfRange) {
   std::unique_ptr<Weapon> sword1 = std::make_unique<Sword>(10, "Excalibur", 100);
   std::unique_ptr<Weapon> feather1 = std::make_unique<Feather>(50, "Pen", 200);
   std::unique_ptr<Weapon> sword2 = std::make_unique<Sword>(20, "Wooden stick", 15);

   Player player{100, 500, 10.f, 5, nullptr};

   player.purchaseWeapon(std::move(sword1));
   player.purchaseWeapon(std::move(feather1));
   player.purchaseWeapon(std::move(sword2));

   EXPECT_EQ(player.getWeaponInventory().size(), 3);

   player.pickWeapon(1);
   EXPECT_EQ(player.getCurrentWeapon(), player.getWeaponInventory()[1].get());

   player.pickWeapon(5);
   EXPECT_EQ(player.getCurrentWeapon(), player.getWeaponInventory()[1].get());


}

TEST(purchaseWeapon, player_withoutEnoughMoney) {
  Player player{100, 100, 10.f, 5,
                nullptr};  // Player avec 500 pièces et sans arme
  std::unique_ptr<Weapon> feather =
      std::make_unique<Feather>(20, "Goose Feather", 150);

  player.purchaseWeapon(std::move(feather));
  EXPECT_EQ(player.getTotalMoney(), 100);  // Le joueur n'a pas depensé d'argent

  EXPECT_EQ(player.getWeaponInventory().size(),
            0);  // Le joueur n'a pas d'arme dans son inventaire
}

}
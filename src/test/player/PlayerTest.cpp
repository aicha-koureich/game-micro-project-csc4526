#include <gtest/gtest.h>

#include "Entities/Enemy.hpp"
#include "Entities/Entity.hpp"
#include "Entities/Player.hpp"
#include "Factories/Factory.h"
#include "Weapons/Feather.h"
#include "Weapons/Sword.h"

namespace Player_test {
// Test de l'épée avec calcul des dégâts et de la performance
TEST(increaseNoseSize, noseSize_increasesAfterAFight) {
  Sword sword{10, "Excalibur", 100};
  // Constructeur : maxHp, money, size, maxMana, defense, currentWeapon
  Player player{100, 50, 10.f, 50, 5, &sword};

  player.increaseNoseSize(0);

  EXPECT_FLOAT_EQ(player.getNoseSize(), 20.f);
}

TEST(takeDamage, player_takeDamage) {
  Sword sword{10, "Excalibur", 100};
  Enemy enemy{100, 2.0f, 10, 20, 2};  // Ennemi qui fait 10 de dégâts
  Player player{100, 50, 10.f,
                50,  5,  &sword};  // Player avec 5 points de défense

  enemy.enemyAttack(player, 1.f);  // Ennemi inflige 10 - 5 = 5 dégâts

  EXPECT_EQ(player.getHealthPoints(), 95);
}

TEST(takeDamage, enemyDamageTooLow) {
  Sword sword{10, "Excalibur", 100};  // Epée infligeant 10 points de dégâts
  Enemy enemy{100, 2.0f, 10, 5, 2};   // Ennemi avec 10 points de dégâts
  Player player{100, 50, 10.f,
                50,  15, &sword};  // Player avec 15 points de défense

  enemy.enemyAttack(player,
                    1.f);  // Ennemi inflige 10 - 15 = -5 donc son attaque va
                           // faire 1 point de dégâts

  EXPECT_EQ(player.getHealthPoints(), 99);
}

TEST(takeDamage, enemyKillPlayer) {
  Sword sword{10, "Excalibur", 100};  // Epée infligeant 10 points de dégâts
  Enemy enemy{100, 2.0f, 200, 5, 2};  // Ennemi avec beaucoup d'attaque
  Player player{100, 50, 10.f,
                50,  15, &sword};  // Player avec 15 points de défense

  enemy.enemyAttack(player,
                    1.f);  // Ennemi inflige beaucoup de dégâts, réduit par def

  EXPECT_EQ(player.getHealthPoints(), 0);
}

TEST(playerAttack, player_attacksAnEnemy) {
  Sword sword{10, "Excalibur", 100};  // Epée infligeant 10 points de dégâts
  Enemy enemy{100, 2.0f, 10, 5, 2};   // Ennemi avec 100 hp et 5 def
  Player player{100, 50, 10.f,
                50,  5,  &sword};  // Player avec 5 points de défense

  // On ajoute le troisième paramètre (AttackType) requis par void
  // Player::playerAttack(Enemy&, float, AttackType)
  player.playerAttack(
      enemy, 1.5f,
      AttackType::STRENGTH);  // Player inflige 10*1.5 = 15 points de dégâts

  EXPECT_EQ(enemy.getHealthPoints(), 90);
}

TEST(pickWeapon, player_withoutWeaponTakesAFeatherFromInventory) {
  Player player{100, 500, 10.f, 50, 5, nullptr};  // Player sans arme au départ
  std::unique_ptr<Weapon> feather =
      std::make_unique<Feather>(20, "Goose Feather", 150);

  player.purchaseWeapon(feather);
  EXPECT_EQ(player.getTotalMoney(), 350);

  player.pickWeapon(0);
  EXPECT_EQ(player.getCurrentWeapon(), player.getWeaponInventory()[0].get());
}

TEST(pickWeapon, player_takesAWeaponInInventoryThenOutOfRange) {
  std::unique_ptr<Weapon> sword1 =
      std::make_unique<Sword>(10, "Excalibur", 100);
  std::unique_ptr<Weapon> feather1 = std::make_unique<Feather>(50, "Pen", 200);
  std::unique_ptr<Weapon> sword2 =
      std::make_unique<Sword>(20, "Wooden stick", 15);

  Player player{100, 500, 10.f, 50, 5, nullptr};

  player.purchaseWeapon(sword1);
  player.purchaseWeapon(feather1);
  player.purchaseWeapon(sword2);

  EXPECT_EQ(player.getWeaponInventory().size(), 3);

  player.pickWeapon(1);
  EXPECT_EQ(player.getCurrentWeapon(), player.getWeaponInventory()[1].get());

  player.pickWeapon(5);
  EXPECT_EQ(player.getCurrentWeapon(), player.getWeaponInventory()[1].get());
}

TEST(purchaseWeapon, player_withoutEnoughMoney) {
  Player player{100, 100, 10.f, 50, 5, nullptr};  // Player avec 100 pièces
  std::unique_ptr<Weapon> feather =
      std::make_unique<Feather>(20, "Goose Feather", 150);

  player.purchaseWeapon(feather);
  EXPECT_EQ(player.getTotalMoney(),
            100);  // Le joueur n'a pas dépensé d'argent car l'arme coûte 150
                   // (regarde son cost)

  EXPECT_EQ(player.getWeaponInventory().size(),
            0);  // Le joueur n'a pas d'arme dans son inventaire
}

}  // namespace Player_test
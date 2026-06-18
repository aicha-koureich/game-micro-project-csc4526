#include <gtest/gtest.h>

#include "Entities/Entity.hpp"
#include "Entities/Player.hpp"
#include "Entities/Enemy.hpp"
#include "Weapons/Sword.h"
#include "Weapons/Feather.h"

namespace Player_test {
// Test de l'épée avec calcul des dégâts et de la performance
TEST(increaseNoseSize, noseSize_increasesAfterAFight) {

  Sword sword{10, "Excalibur", 100};
  Player player{100, 50, 10.f, 5, &sword};
  
  player.increaseNoseSize();

  EXPECT_FLOAT_EQ(player.getNoseSize(), 20.f);
}

TEST(takeDamage, player_takeDamage) { 
	Sword sword{10, "Excalibur", 100};
    Enemy enemy{100, 2.0f, 10, 20, 2};  //Ennemi qui fait 10 de dégâts
    Player player{100, 50, 10.f, 5, &sword};    //Player avec 5 points de défense 

    enemy.enemyAttack(player); //Ennemi inflige 10 - 5 = 5 dégats

    EXPECT_EQ(player.getHealthPoints(), 95);

}
}
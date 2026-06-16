#include <gtest/gtest.h>

#include "Entities/Entity.hpp"
#include "Entities/Enemy.hpp"
#include "Weapons/Feather.h"
#include "Weapons/Sword.h"

namespace RPG_Combat_test {

// Test de l'épée avec calcul des dégâts et de la performance
TEST(SwordTest, attack_appliesDamageWithPerformanceAndDefense) {
  // Arrange (Préparation)
  // Ennemi : 100 HP, Sensibilité = 1.0, Dégâts = 10, Défense = 5, Niveau = 1
  Enemy enemy{100, 1.0f, 10, 5, 1};
  Enemy& enemyRef = enemy;
  Sword sword{10, "Excalibur", 100};

  // Act (Action)
  // Dégâts bruts : 10 * 1.5 = 15. Dégâts nets : 15 - 5 (défense) = 10
  sword.attack(enemyRef, 1.5f);

  // Assert (Vérification)
  EXPECT_EQ(enemy.getHealthPoints(), 90);
}

// Test du débuff de défense de la plume
TEST(FeatherTest, attack_reducesEnemyDefenseWithoutHurting) {
  // Arrange
  // Ennemi : 100 HP, Sensibilité = 2.0, Dégâts = 10, Défense = 20, Niveau = 2
  Enemy enemy{100, 2.0f, 10, 20, 2};
  Enemy& enemyRef = enemy;
  Feather feather{15, "Plume d'Oie", 50};
  feather.setDebuffChoice(DebuffType::DEFENSE);

  // Act
  // Effet : 15 * 1.0 = 15. Réduction : (15 * 2.0) / 2 = 15. Nouvelle défense :
  // 20 - 15 = 5
  feather.attack(enemyRef, 1.0f);

  // Assert
  EXPECT_EQ(enemy.getCurrentDefense(),
            5);  
  EXPECT_EQ(enemy.getHealthPoints(),
            100);  
}

// Test de la réinitialisation de fin de tour
TEST(EnemyTest, resetTurnDebuffs_restoresOriginalStats) {
  // Arrange
  Enemy enemy{100, 2.0f, 10, 20, 2};
  Enemy& enemyRef = enemy;
  Feather feather{15, "Plume d'Oie", 50};
  feather.setDebuffChoice(DebuffType::DEFENSE);

  // Act
  feather.attack(enemyRef, 1.0f);  
  enemy.resetTurnDebuffs();     

  // Assert
  EXPECT_EQ(enemy.getCurrentDefense(),
            20);  // La défense doit être revenue à sa valeur de base
}

}  // namespace RPG_Combat_test
#include <gtest/gtest.h>

#include "Entities/Enemy.hpp"
#include "Entities/Entity.hpp"
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
  // On passe 1.0f en multiplicateur de base (aucun item actif)
  sword.attack(enemyRef, 1.5f, 1.0f);

  // Assert (Vérification)
  EXPECT_EQ(enemy.getHealthPoints(), 90);
}

// Test du débuff de défense de la plume
TEST(FeatherTest, attack_reducesEnemyDefenseWithoutHurting) {
  // Arrange
  // Ennemi : 100 HP, Sensibilité = 2.0, Atk = 10, Def = 20, Niveau = 2
  Enemy enemy{100, 2.0f, 10, 20, 2};
  Enemy& enemyRef = enemy;

  // On met directement 30 en effet de base (ou 15 avec l'encre appliquée)
  Feather feather{30, "Plume d'Oie", 50};
  feather.setDebuffChoice(DebuffType::DEFENSE);

  // Act
  // Effet : 30 * 1.0 (perf) * 1.0 (multiplicateur joueur) = 30.
  // Réduction de défense = 30.
  // Nouvelle défense : 20 - 30 = -10, plafonnée à 0.
  feather.attack(enemyRef, 1.0f, 1.0f);

  // Assert
  EXPECT_EQ(enemy.getCurrentDefense(), 0);
  EXPECT_EQ(enemy.getHealthPoints(), 100);
}

// Test de la réinitialisation de fin de tour
TEST(EnemyTest, resetTurnDebuffs_restoresOriginalStats) {
  // Arrange
  Enemy enemy{100, 2.0f, 10, 20, 2};
  Enemy& enemyRef = enemy;
  Feather feather{15, "Plume d'Oie", 50};
  feather.setDebuffChoice(DebuffType::DEFENSE);

  // Act
  feather.attack(enemyRef, 1.0f, 1.0f);
  enemy.resetDefenseDebuff();

  // Assert
  EXPECT_EQ(enemy.getCurrentDefense(),
            20);  // La défense doit être revenue à sa valeur de base
}

// Test 4 : Coup fatal - Les PV ne doivent pas descendre en dessous de 0
TEST(SwordTest, attack_fatalBlowDoesNotResultInNegativeHP) {
  // Arrange
  Enemy enemy{20, 1.0f, 10, 5, 1};  // Seulement 20 HP
  Enemy& enemyRef = enemy;
  Sword sword{100, "Épée Divine", 500};  // Une épée surpuissante (100 dégâts)

  // Act
  // Dégâts bruts : 100 * 1.0 = 100. Dégâts nets : 100 - 5 = 95.
  // 20 PV - 95 dégâts = -75. Mais la sécurité doit bloquer à 0 !
  sword.attack(enemyRef, 1.0f, 1.0f);

  // Assert
  EXPECT_EQ(enemy.getHealthPoints(), 0);
}

// Test 5 : Arme inefficace ou Défense impénétrable - Dégâts minimums garantis
TEST(SwordTest, attack_highDefenseEnsuresAtLeastOneDamage) {
  // Arrange
  Enemy enemy{100, 1.0f, 10, 50, 1};  // Une défense colossale de 50
  Enemy& enemyRef = enemy;
  Sword sword{10, "Cure-dent", 5};  // Petite arme (10 dégâts)

  // Act
  // Dégâts nets : 10 - 50 = -40. La sécurité doit forcer 1 point de dégât
  // minimum.
  sword.attack(enemyRef, 1.0f, 1.0f);

  // Assert
  EXPECT_EQ(enemy.getHealthPoints(), 99);  // 100 - 1 = 99
}

// Test 6 : Débuff massif de défense - Ne doit pas descendre sous 0
TEST(FeatherTest, attack_massiveDebuffCannotMakeDefenseNegative) {
  // Arrange
  Enemy enemy{100, 1.0f, 10, 10, 1};  // Défense de 10
  Enemy& enemyRef = enemy;
  Feather feather{100, "Plume Divine", 500};  // Éloquence de 100
  feather.setDebuffChoice(DebuffType::DEFENSE);

  // Act
  // Réduction de 100 * 1.0 = 100 sur une défense de 10.
  // La sécurité doit bloquer à 0.
  feather.attack(enemyRef, 1.0f, 1.0f);

  // Assert
  EXPECT_EQ(enemy.getCurrentDefense(), 0);
}

// Test 7 : Débuff massif d'attaque - L'ennemi garde 1 point d'attaque minimum
TEST(FeatherTest, attack_massiveDebuffEnsuresAtLeastOneDamageLeft) {
  // Arrange
  Enemy enemy{100, 1.0f, 15, 10, 1};  // Dégâts de base de 15
  Enemy& enemyRef = enemy;
  Feather feather{100, "Plume Divine", 500};
  feather.setDebuffChoice(DebuffType::STRENGTH);

  // Act
  // Réduction de 100 * 1.0 = 100 sur une attaque de 15.
  // La sécurité doit bloquer à 1 (et non 0 !).
  feather.attack(enemyRef, 1.0f, 1.0f);

  // Assert
  EXPECT_EQ(enemy.getCurrentDamage(), 1);
}

// Test 8 : Pire QTE possible (Performance = 0)
TEST(SwordTest, attack_zeroPerformanceStillDealsMinimumDamage) {
  // Arrange
  Enemy enemy{100, 1.0f, 10, 0, 1};  // Pas de défense pour simplifier
  Enemy& enemyRef = enemy;
  Sword sword{50, "Épée Lourde", 100};

  // Act
  // Le joueur rate complètement son QTE (0.0f).
  // Dégâts bruts = 50 * 0 = 0.
  // La méthode takeDamage doit tout de même infliger le minimum syndical : 1.
  sword.attack(enemyRef, 0.0f, 1.0f);

  // Assert
  EXPECT_EQ(enemy.getHealthPoints(), 99);
}

}  // namespace RPG_Combat_test
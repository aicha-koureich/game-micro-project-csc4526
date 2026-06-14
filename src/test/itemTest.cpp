#include <iostream>
#include <cassert>
#include "Entities/Player.hpp"
#include "Item/GasconeWine.hpp"
#include "Item/InkFlask.hpp"
#include "Item/RoxanneLetter.hpp"
#include "Weapons/Sword.h"
#include "Weapons/Feather.h"

// Note: Assure-toi que MAX_HEALTH_POINTS et MAX_WEAPON_EFFECT sont bien definis
// dans tes en-tetes respectifs (Player.hpp et Weapon.h par exemple).

void testGasconeWine() {
    Player player(100);
    GasconeWine wine(5, 0.5f); // 50% de bonus
    
    // 1. Test de soin en pourcentage (50 + 50% = 75)
    player.setHealthPoints(50);
    wine.used(player);
    assert(player.getHealthPoints() == 75 && "ECHEC: Le vin n'a pas applique le boost de 50% correctement.");

    // 2. Test du plafond (Maximum 100)
    // 80 + 50% de 80 = 120 -> Plafonné à 100
    player.setHealthPoints(80);
    wine.used(player);
    assert(player.getHealthPoints() == 100 && "ECHEC: Le joueur a depasse les PV maximum !");

    std::cout << "[OK] testGasconeWine" << std::endl;
}

void testInkFlask() {
    Player player(100);
    InkFlask ink(10, 0.5f); // 50% de boost
    Sword mySword(WeaponType::SWORD, "Epee", 20, 10);
    Feather myFeather(WeaponType::FEATHER, "Plume", 10, 5);

    // 1. Test sur l'épée (doit échouer - l'encre ne fonctionne pas sur l'épée)
    player.setCurrentWeapon(&mySword);
    assert(ink.used(player) == false && "ECHEC: L'encre s'est consommee sur l'epee.");
    
    // 2. Test sur la plume (boost 10 * 1.5 = 15)
    player.setCurrentWeapon(&myFeather);
    ink.used(player);
    assert(myFeather.getEffect() == 15 && "ECHEC: La plume n'a pas ete boostee a 15 (10 * 1.5).");

    // 3. Test du plafond (100)
    myFeather.setEffect(80);
    ink.used(player); // 80 * 1.5 = 120 -> Plafonné à 100
    assert(myFeather.getEffect() == 100 && "ECHEC: L'encre a fait depasser le MAX_WEAPON_EFFECT !");

    std::cout << "[OK] testInkFlask" << std::endl;
}

void testRoxanneLetter() {
    Player player(100);
    RoxanneLetter letter(15, 0.5f); // 50% de boost
    Sword mySword(WeaponType::SWORD, "Epee", 20, 10);
    Feather myFeather(WeaponType::FEATHER, "Plume", 10, 5);

    // 1. Test sur la plume (doit échouer - la lettre ne fonctionne pas sur la plume)
    player.setCurrentWeapon(&myFeather);
    assert(letter.used(player) == false && "ECHEC: La lettre s'est consommee sur la plume.");

    // 2. Test sur l'épée (boost 20 * 1.5 = 30)
    player.setCurrentWeapon(&mySword);
    letter.used(player);
    assert(mySword.getEffect() == 30 && "ECHEC: L'epee n'a pas ete boostee a 30 (20 * 1.5).");

    // 3. Test du plafond
    mySword.setEffect(80);
    letter.used(player); // 80 * 1.5 = 120 -> Plafonné à 100
    assert(mySword.getEffect() == 100 && "ECHEC: La lettre a fait depasser le MAX_WEAPON_EFFECT !");

    std::cout << "[OK] testRoxanneLetter" << std::endl;
}

int main() {
    std::cout << "--- LANCEMENT DES TESTS UNITAIRES ---\n" << std::endl;

    testGasconeWine();
    testInkFlask();
    testRoxanneLetter();

    std::cout << "\n--- TOUS LES TESTS ONT REUSSI ! ---" << std::endl;
    return 0;
}
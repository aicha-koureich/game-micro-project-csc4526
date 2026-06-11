#include <iostream>
#include "Player.hpp"
#include "Weapons/Weapon.h"

Player::Player(int hp) : Entity(hp), baseDamage(5), baseDefense(2), noseSize(0), speed(1.0f), isBlocking(false){
    
}

AttackType Player::getCurrentAttackType() { return currentAttackType; }
void Player::setAttackType(AttackType type) { currentAttackType = type; }

Weapon* Player::getCurrentWeapon() { return (Weapon*)currentWeapon; }

void Player::receiveDamage(int trueDamage, AttackType type) {

}

void Player::takeDamage(int attackRes) { healthPoints -= attackRes; }

void Player::attack(const Entity& target, AttackType type){
    //Calcul des dégâts que va faire le joueur
    int baseDamage = baseDamage;


    
}

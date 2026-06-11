#include <iostream>
#include "Player.hpp"
#include "Weapons/Weapon.h"

Player::Player(int hp) : Entity(hp), baseDamage(5), baseDefense(2), noseSize(0), speed(1.0f), isBlocking(false){
    
}


void Player::takeDamage(AttackType type, int attackRes){

}

void Player::attack(const Entity& target, AttackType type){
    //int damages = this-> currentWeapon;
    //Calcul des dégâts que va faire le joueur

    
}

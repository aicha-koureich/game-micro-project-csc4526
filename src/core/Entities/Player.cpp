#include <iostream>
#include "Player.hpp"

Player::Player(int hp) : Entity(hp), baseDamage(5), baseDefense(2), noseSize(0), speed(1.0f), isBlocking(false){
    
}



void Player::takeDamage(const Entity& attacker, AttackType type){

}

void Player::attack(const Entity& target, AttackType type){
    //int damages = this-> currentWeapon;
    
}

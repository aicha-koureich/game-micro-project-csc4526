#include <iostream>
#include "Player.hpp"

Player::Player(int hp) : Entity(hp), baseDamage(5), baseDefense(2), noseSize(0), speed(1.0f), isBlocking(false){
    
}

//m

void Player::takeDamage(int attackRes){

}

void Player::attack(const Entity& target, AttackType type){
    //int damages = this-> currentWeapon;
    
}

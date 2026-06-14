#include <iostream>
#include "Player.hpp"
#include "Weapons/Weapon.h"

Player::Player(int hp) : Entity(hp){}


void Player::takeDamage(int attackRes){}

int Player::attack(const Entity& target){return 0;}
    //int damages = this-> currentWeapon;
    //Calcul des d�g�ts que va faire le joueur


#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <vector>
#include "Entity.hpp"
#include "Weapon.h"
using namespace std;

class Player : public Entity {
 private:
  int totalMoney;
  int noseSize;
  float speed;
  int eloquenceEffect;
  Weapon* currentWeapon;
  vector<unique_ptr<Weapon>> weaponInventory;
  //vector<std::unique_ptr<Items>> itemInventory;

 public:
  Player(int hp);
  ~Player() override = default;
  void takeDamage(int attackRes) override;
  int attack(const Entity& target) override;
  void pickWeapon(size_t idx);
  void increaseNoseSize();
  /*void useItem(size_t idx);
  void addItem(std::unique_ptr<Item>);
  const vector<std::unique_ptr<Item>>& getItemInventory() const{return itemInventory;}
  */
  void addWeapon(std::unique_ptr<Weapon>);
  Weapon* getCurrentWeapon() const{ return currentWeapon;}
  const vector<std::unique_ptr<Weapon>>& getWeaponInventory() const{ return weaponInventory;}
  int getTotalMoney() const{return totalMoney;}

};
#endif
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <vector>
#include "Entity.hpp"
#include "Weapons/Weapon.h"
using namespace std;

class Player : public Entity {
 private:
  int totalMoney;
  float noseSize;
  int baseDefense;
  Weapon* currentWeapon;
  vector<unique_ptr<Weapon>> weaponInventory;
  //vector<std::unique_ptr<Items>> itemInventory;

 public:
  Player(int hp);
  ~Player() override = default;

  // Getters
  int getTotalMoney() const { return totalMoney; }

  Weapon* getCurrentWeapon() const { return currentWeapon; }

  const vector<std::unique_ptr<Weapon>>& getWeaponInventory() const {
    return weaponInventory;
  }

  /* const vector<std::unique_ptr<Item>>& getItemInventory() const {
    return itemInventory;
  } */

  //IncreaseNoseSize
  void increaseNoseSize();

  //Weapon Methods  
  void pickWeapon(size_t idx);
  void purchaseWeapon(std::unique_ptr<Weapon>);

  //Attack Methods
  void takeDamage(int attackRes) override;
  void playerAttack(Entity& target, float performance);

  
  //Items Methodes
  /*void useItem(size_t idx);
  void addItem(std::unique_ptr<Item>);
  
  */
  


};
#endif
#ifndef WEAPON_H
#define WEAPON_H
#include <string>
#include "Entities/Entity.hpp"

/* - les effets des armes sont sous une variable weaponEffect
   - Les getters font la meme chose pour sword et feather donc pas besoin qu'ils soient virtuels pures 
   - J'ai ajouté nom, comme ca ils pourront apparaitre dans le catalogue et le jeu en général
   - AttackType a plus trop d'utilité en fait, on sait qu'une feather c'est eloq, et la logique d'attaque est dans l'arme mtn donc info redondante*/
#define MAX_WEAPON_EFFECT 100

enum class WeaponType{SWORD, FEATHER};
   
class Weapon {
 protected:
  std::string name;
  WeaponType type;
  int weaponEffect;
  int cost;

 public:
  Weapon(WeaponType t, const std::string& n, int effect, int c): type(t), name(n), weaponEffect(effect), cost(c){} 
  virtual ~Weapon() = default;
  virtual int attack(Entity&) = 0;
  virtual int getEffect() const{ return weaponEffect;}
  virtual void setEffect(int effect){weaponEffect = effect;}
  virtual WeaponType getType() const{ return type;}

};
#endif
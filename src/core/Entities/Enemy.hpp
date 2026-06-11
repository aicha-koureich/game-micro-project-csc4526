#include "Entity.hpp"
#include "AttackType.hpp"
#include "Weapons/Weapon.h"

class Enemy : public Entity {
	private:
		const AttackType sensitivity;
        int enemyDamage;
        std::pair < std::unique_ptr<Weapon>, std::unique_ptr<Weapon>>

	public:
        Enemy(int healthPoints);
         ~Enemy() override = default;
        const AttackType getSensitivity();
        void takeDamage(AttackType type, int attackRes) override;
        void attack(const Entity& target, AttackType type) override;
        std::pair < std::unique_ptr<Weapon>, std::unique_ptr<Weapon>> dropWeapons();
};
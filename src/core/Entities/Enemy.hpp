#include "Entity.hpp"
#include "AttackType.hpp"

class Enemy : public Entity {
	private:
		const AttackType sensitivity;
        int enemyDamage;
        //std::pair < std::unique_ptr<Weapon>, std::unique_ptr<Weapon>>

	public:
        const AttackType getSensitivity();
        void takeDamage(const Entity& attacker, int attackRes) override;
        void attack(const Entity& target, AttackType type) override;
        // std::pair < std::unique_ptr<Weapon>, std::unique_ptr<Weapon>> dropWeapons();
};
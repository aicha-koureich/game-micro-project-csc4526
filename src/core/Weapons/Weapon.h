#ifndef WEAPON_H
#define WEAPON_H

enum class AttackType {
	Force,
	Eloquence
};

class Weapon {
	public:
		virtual ~Weapon() = default;

		virtual int getEffect() const = 0;
		virtual AttackType getType() const = 0;
};

#endif
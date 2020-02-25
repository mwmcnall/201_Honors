#include "Weapon.h"

Weapon::Weapon() : attack(0), crit_rate(0), type(0) {};
Weapon::Weapon(unsigned int p_attack=0, unsigned int p_crit_rate = 0, unsigned int p_type = 0) :
	attack(p_attack), crit_rate(p_crit_rate), type(p_type) {};
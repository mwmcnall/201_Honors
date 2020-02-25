#include "Creature.h"
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <cstdlib>

//std::vector<bool> resist, status;

void Creature::Initialize_Creature() {
	max_HP = hp;
	Initialize_Status();
	Initialize_Resist();
}

// Default Constructor
Creature::Creature() :
	name(""), hit_perc(0), hp(0), attack(0), defense(0), mag_defense(0),
	eva_perc(0), exp(0), turn_ID(99) {
	
	Initialize_Creature();
}

Creature::Creature(std::string p_name, unsigned int p_hitPerc,
	unsigned int p_hp, unsigned int p_attack, unsigned int p_defense, unsigned int p_mag_defense,
	unsigned int p_eva_perc, unsigned int p_exp, unsigned int p_turn_id)
	: name(p_name), hit_perc(p_hitPerc), hp(p_hp), attack(p_attack), defense(p_defense),
	  mag_defense(p_mag_defense), eva_perc(p_eva_perc), exp(p_exp), turn_ID(p_turn_id) {

	Initialize_Creature();

}


float Creature::Rand_Zero_One() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void Creature::Target_Damage(unsigned int damage) {
	this->hp -= damage;
	return;
}

int Creature::Roll_Hit(Creature* target) {
	int hitRoll = BASE_HIT_CHANCE;
	if (status[blind])
		hitRoll -= 40;
	if (target->status[blind])
		hitRoll += 40;

	/*
	# TODO: Decide how to handle elements for both enemies and characters
	# if attack_command:
	#     if self.Weapon.elem in target.elem_aff:
	#         hit_roll += 40
		# TODO: If target weak to spell element then add 40
	*/

	// First calculation caps at 255
	hitRoll = std::min((hitRoll + static_cast<int>(hit_perc)), 255);

	return hitRoll;

}

bool Creature::Return_Hit_Bool(Creature* target, bool attack_command) {
	
	int hitRoll = Roll_Hit(target);

	if (hitRoll == 0)
		return true;
	else if (hitRoll == 255)
		return false;

	// This reflects a percent change to hit, returning true if the random roll hits
	if (Rand_Zero_One() < ((static_cast<float>(hitRoll + 1.0) / 201.0)))
		return true;

	return false;

}

int Creature::Attack_Target(Creature* target) {
	// Roll damage and hit target

	double damage = 0;

	if (this->Return_Hit_Bool(target)) {
		// 1 is the minimum damage
		double first_val = floor(Rand_Zero_One() * static_cast<double>(this->attack)) - target->defense;
		damage = fmax(first_val, 1.0);
		target->Target_Damage(static_cast<unsigned int>(damage));
		return static_cast<int>(damage);
	}
	return 0;
}

void Creature::Lower_HP(const int health_minus) {
	hp -= health_minus;
	return;
}

void Creature::Gain_HP(const int health_plus) {
	hp += health_plus;
	return;
}

void Creature::Use_Spell() {
	return;
}

bool Creature::If_Dead() {
	// Checks if hp underflowed
	if (hp > max_HP)
		return true;
	return false;
}

void Creature::Initialize_Status() {
	for (int i = 0; i < NR_STATUSES; i++)
		status.push_back(0);
	return;
}

void Creature::Initialize_Resist() {
	std::vector<bool> resist;
	return;
}

Battle_History* Creature::AI_Turn() {
	Battle_History b_h;
	return &b_h;
}
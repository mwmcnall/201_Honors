#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "Creature.h"
class Enemy :
	public Creature
{
private:
	unsigned int Target_Slot(unsigned int slot);
public: // Variables
	unsigned int id, gil, hits;
	std::vector<std::string> locations;
	// TODO: std::vector<Spell> spells;
	// TODO: std::vector<Skill> skills;
public: // Methods
	Enemy();
	Enemy(std::string p_name, unsigned int p_id, unsigned int p_hitPerc,
		unsigned int p_hp, unsigned int p_attack, unsigned int p_defense, unsigned int p_mag_defense,
		unsigned int p_eva_perc, unsigned int p_exp, unsigned int p_turn_id,
		unsigned int p_gil, unsigned int p_hits);
	unsigned int Choose_Target(Round* round);
	Battle_History* AI_Turn(Round* round) override;
	// TODO: void Use_Spell(Spell spell);
	// TODO: void Use_Skill(Skill skill);
};

#endif
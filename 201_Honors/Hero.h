#pragma once
#ifndef HERO_H
#define HERO_H
#include "Creature.h"
#include "Weapon.h"
#include "Armor.h"
#include "Battle.h"
#include <cstdlib>
#include <vector>
#include <string>

class Hero : 
	public Creature {

private: // Variables
	// Vector for job class checking
	std::vector<bool> job_class_vec = {false, false, false, false, false, false, false, 
		false, false, false, false, false};

	// The exp table to determine levels is the same for every Job Class, so it can be static
	static const std::vector<unsigned int> expTable;
	// Stats for Hero
	unsigned int str, agi, inte, vit, luck, eva, lvl;

private: // Methods
	unsigned int Attack_Formula();
	void Level_Up();
	bool If_Level();
	void Gain_EXP(int exp_amount) { this->exp += exp_amount; }

public: // Variables
	// const static enum for job class
	enum job_class {
		fighter, b_belt, thief, r_mage, w_mage, b_mage,
		knight, master, ninja, r_wiz, w_wiz, b_wiz,
		// Use this last item in the ENUM as a way to instantiate the bool vectors
		NR_JOB_CLASS
	};
	static job_class job_class_enum;
	Weapon weapon = Weapon(0, 0, 0);
	Armor armor = Armor(0, 0);

public: // Methods
	Hero();
	Hero(std::string p_name, unsigned int p_hitPerc,
		unsigned int p_hp, unsigned int p_attack, unsigned int p_defense, unsigned int p_mag_defense,
		unsigned int p_eva_perc, unsigned int p_exp, unsigned int p_turn_id,
		unsigned int p_str, unsigned int p_agi, unsigned int p_inte, unsigned int p_vit,
		unsigned int p_luck, unsigned int p_eva, int p_job);

	//void Set_Battle(Battle battle);
	Battle_History* AI_Turn(Round*) override;

	// Get / Set Methods
	unsigned int Get_Str() { return str; }
	void Set_Str(unsigned int p_str) { str = p_str; }
	unsigned int Get_Agi() { return agi; }
	void Set_Agi(unsigned int p_agi) { agi = p_agi; }
	unsigned int Get_Inte() { return inte; }
	void Set_Inte(unsigned int p_inte) { inte = p_inte; }
	unsigned int Get_Vit() { return vit; }
	void Set_Vit(unsigned int p_vit) { vit = p_vit; }
	unsigned int Get_Luck() { return luck; }
	void Set_Luck(unsigned int p_luck) { luck = p_luck; }
	unsigned int Get_Eva() { return eva; }
	void Set_Eva(unsigned int p_eva) { eva = p_eva; }
	unsigned int Get_Lvl() { return lvl; }
	void Set_Lvl(unsigned int p_lvl) { lvl = p_lvl; }
	std::vector<bool> Get_Job() { return job_class_vec; }
	void Set_Job(unsigned int job) { job_class_vec.at(job) = true; }

};
#endif
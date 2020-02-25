#ifndef CREATURE_H
#define CREATURE_H
//#include "Battle.h"
#include <cstdlib>
#include <vector>
#include <string>

/*
  This struct allows me to have a function that returns all of these items
  Used to write the history of a turn to file
  Each data type matches a column header of the battle_history.txt file
*/
struct Battle_History {
	unsigned int round, turn;
	std::string self_name, target_name, attack_type;
	unsigned int action_result;
};

struct Battle_Result {
	std::vector<std::string> enemy_names, hero_names;
	int round_tot, turn_tot;
	std::string victor;
	int hp_loss_victor;
};

// Class declaration, allows Creature and Round to use each other's types and wait for definition
// to appear during compile
class Battle;

class Creature {

private: // Variables
	// There is only one active battle for any enemy / Hero, so this can be static on creature and set once
	static const int BASE_HIT_CHANCE = 168;
	unsigned int max_HP;

private: // Methods
	void Initialize_Creature();
	void Initialize_Status();
	void Initialize_Resist();	

protected:
	Battle* battle;

public: // Variables
	std::string name;
	unsigned int hit_perc, hp, attack, defense, mag_defense, eva_perc, exp, turn_ID;

	enum Statuses {
		blind, confused, darkness, fear, silence, sleep, slow, paralysis, stone, ko,
		// Use this last item in the ENUM as a way to instantiate the bool vectors
		NR_STATUSES
	};
	static Statuses statuses;
	// TODO: static const ai = ai

	std::vector<bool> resist, status;
	
public: // Methods

	// Default Constructor
	Creature();

	// Valued Constructor
	Creature(std::string name, unsigned int hitPerc,
		unsigned int hp, unsigned int attack, unsigned int defense, unsigned int mag_defense,
		unsigned int eva_perc, unsigned int exp, unsigned int turn_ID);

	float Rand_Zero_One();
	void Target_Damage(unsigned int damage);
	int Roll_Hit(Creature* target);
	bool Return_Hit_Bool(Creature* target, bool attack_command = true);
	int Attack_Target(Creature* target);
	void Lower_HP(const int health_minus);
	void Gain_HP(const int health_plus);
	void Use_Spell();
	bool If_Dead();
	// Meant to be overwritten by the interhited type
	Battle_History* AI_Turn();
	// TODO: Look up how to set a bool vector using an enum value

	// Get / Set Methods
	unsigned int Get_Max_HP() { return max_HP; }
	void Set_Max_HP(unsigned int mHP) { max_HP = mHP; }

	// Destructor
	~Creature() {

	}
};

#endif
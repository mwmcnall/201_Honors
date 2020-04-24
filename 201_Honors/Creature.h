#ifndef CREATURE_H
#define CREATURE_H
#include <cstdlib>
#include <vector>
#include <string>

// Declared for use with struct, defined below
class Creature;
// Declared here to allow compile, attempting to include will cause error for circular inclusion
class Round;

/*
  This struct allows me to have a function that returns all of these items
  Used to write the history of a turn to file
  Each data type matches a column header of the battle_history.txt file
*/
struct Battle_History {
	unsigned int round, turn, turn_id;
	std::string self_name, target_name, attack_type;
	unsigned int action_result;
	Creature* target;
};

class Creature {

private: // Variables
	static const int BASE_HIT_CHANCE = 168;
	unsigned int max_HP;

private: // Methods
	void Initialize_Creature();
	void Initialize_Status();
	void Initialize_Resist();	

protected:
	Round* battle;

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
	// For whether or not the creature has that resist or is afflicted with a status
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
	void Gain_HP(const int health_plus);
	void Use_Spell();
	bool If_Dead();
	// Meant to be overwritten by the interhited type
	virtual Battle_History* AI_Turn(Round* round) = 0;
	// TODO: Look up how to set a bool vector using an enum value

	// Get / Set Methods
	unsigned int Get_Max_HP() { return max_HP; }
	void Set_Max_HP(unsigned int mHP) { max_HP = mHP; }

	// Destructor
	~Creature() {

	}
};

#endif
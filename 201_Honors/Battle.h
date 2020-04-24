#pragma once
#ifndef BATTLE_H
#define BATTLE_H
#include "Round.h"
//#include "Hero.h"
//#include "Enemy.h"

// To organize information for the battle_result.txt file
struct Battle_Result {
	std::vector<std::string> enemy_names, hero_names;
	int round_tot, turn_tot;
	std::string victor;
	int hp_loss_victor;
};

class Battle :
	public Round
{
private: // Methods
	void Write_Vector_To_File(std::ofstream& outFS, std::vector<std::string> vec);
	void Update_Battle_Result(Battle_Result* b_r);
public: // Variables
	//std::vector<Hero> participant_heroes;
	//std::vector<Enemy> participant_enemies;
	unsigned int current_target_ID = -1;
public:
	Battle();
	Battle(std::vector<Creature*> participants);
	void Start_Battle();
	bool Is_Target_Defeated();
	bool If_Battle_Over();
	bool If_No_Participants();
	bool If_All_Health_Zero();
	void Update_Battle_History(Turn turn);
	void Update_Battle_Result();
	void Set_Current_Target();
	void Remove_Participant();
};

#endif
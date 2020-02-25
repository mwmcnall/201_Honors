#pragma once
#ifndef BATTLE_H
#define BATTLE_H
#include "Round.h"
//#include "Hero.h"
//#include "Enemy.h"
class Battle :
	public Round
{
	// TODO: Create structs that hold the shape of information for the .csvs
private: // Methods
	
public: // Variables
	//std::vector<Hero> participant_heroes;
	//std::vector<Enemy> participant_enemies;
	std::string victor = "";
	unsigned int current_target_ID = -1;
public:
	Battle();
	void Start_Battle();
	bool Is_Target_Defeated();
	bool If_Battle_Over();
	bool If_No_Participants();
	bool If_All_Health_Zero();
	void Update_Battle_History(Turn turn);
	void Update_Battle_Result();
	void Set_Current_Target();
	void Remove_Participant();
	Creature* Participant_From_ID(unsigned int target_id);
};

#endif
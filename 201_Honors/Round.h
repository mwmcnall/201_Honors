#pragma once
#ifndef ROUND_H
#define ROUND_H
#include "Turn.h"
#include "Creature.h"
#include <iostream>
#include <fstream>

class Round :
	public Turn
{
private: // Variables
	std::string victor;
private: // Methods
	// Initialization
	void Initialize_Round();
	void Initialize_Participant_Turn_IDs();
	void Initialize_Data_File_Columns(const std::string file_name, const std::vector<std::string> file_cols);
	// File work
	bool Create_File_If_Not_Exists(const std::string file_name);
	unsigned int Get_Data_Entry_ID(const std::string file_name);
	void Write_Vector_To_File(std::ofstream& outFS, std::vector<std::string> vec);
	void Update_Battle_History(Battle_History* b_h);
	void Update_Battle_Result(Battle_Result* b_r);
	// Target
	void Set_Current_Target(Creature* new_target);
	bool Target_Defeated();
	// Participants
	void Remove_Participant();
	void Remove_Creature_From_Vector(std::vector<Creature*> vec);
	std::vector<Creature*> Subset_Enemies();
	std::vector<Creature*> Subset_Heroes();
	bool End_Condition();
protected: // Variables
	// Columns for files, automatically written in .csv format to separate files
	const std::vector<std::string> battle_history_cols = { "b_h_id", "round_num",
		"turn_num", "self_name", "target_name", "action", "action_result" };
	const std::vector<std::string> battle_result_cols = { "b_r_id","enemies", "characters", "round_tot",
		"turn_tot", "victor", "hp_loss_victor", "b_h_id" };
public: // Variables
	unsigned int rounds = 1;
	// Used as reference to write correct IDs to file
	unsigned int b_r_id, b_h_id;
	// Current target in battle
	Creature* target = nullptr;
	// Paticipants
	std::vector<Creature*> participants;
	std::vector<unsigned int> participant_IDs;
	std::vector<Creature*> participant_heroes;
	std::vector<Creature*> participant_enemies;
public: // Methods
	// Instantiation
	Round();
	Round(unsigned int pRounds, std::vector<Creature*> participants);
	// Main method of class, everything else revolves aorund this
	bool Battle_Round();
	void Increase_Round() { rounds++; }
	// Getters / Setters
	std::string Get_Victor() { return victor; }
	void Set_Victor(std::string victor) { this->victor = victor; }

};

#endif
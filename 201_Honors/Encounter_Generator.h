#pragma once
#ifndef ENC_GEN_H
#define ENC_GEN_H

#include <vector>
#include "Enemy.h"
#include "Enemy_Generator.h"

struct Spawn_Amount {
	int min, max;
};

struct Encounter {
	std::vector<int> enemy_ids;
	std::vector<Spawn_Amount*> enemy_spawns;
	float chance;
};

const std::string AREA_FILE_LOC = "./data/areas.txt";
const std::string ENCOUNTERS_FILE_LOC = "./data/encounters.txt";
const int TOTAL_ENEMIES = 6;

class Encounter_Generator
{
private:
	Enemy_Generator* E_G;
	std::vector<Encounter*> possible_encounters;
	Encounter* current_encounter;
	std::vector<Creature*> encounter_enemies;
private:
	int Area_Name_To_ID(std::string area_name);
	void Instantiate_Possible_Encounters(int area_id);
	std::string Read_Stream_To_Character(std::istringstream& iss, char end_char, char ignore_char);
	Encounter* Create_Encounter(std::istringstream& iss);
	Encounter* Roll_Encounter();
	std::vector<Creature*> Instantiate_Encounter_Enemies();
	int Roll_Spawn_Amount(Spawn_Amount* s_a);
public:
	Encounter_Generator();
	~Encounter_Generator();
	std::vector<Creature*> Spawn_Encounter(std::string area_name);
};

#endif
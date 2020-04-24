#include "Encounter_Generator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

int Encounter_Generator::Area_Name_To_ID(std::string area_name){
	// Open the file
	std::ifstream inFS;
	inFS.open(AREA_FILE_LOC, std::ofstream::out | std::ofstream::app);
	std::string line, name;

	// Skip first line which is just the headers
	std::getline(inFS, line);
	// Return id if area name matches line found in file
	while (std::getline(inFS, line)) {
		replace(line.begin(), line.end(), ',', ' ');
		std::istringstream iss(line);
		int id;
		iss >> id;
		getline(iss, name);
		if (name.find(area_name) != std::string::npos)
			return id;
	}

	inFS.close();
	std::cout << "Area name not found? Check for mis-spellings or if area has not been implemented yet.";
	exit(1);
}

// Creates an Encounter object based on the current stream of input from encounters.txt
Encounter* Encounter_Generator::Create_Encounter(std::istringstream &iss) {

	// Create enemy_ids
	std::string enemy_list = Read_Stream_To_Character(iss, ']', '[');
	replace(enemy_list.begin(), enemy_list.end(), ',', ' ');
	std::istringstream e_iss(enemy_list);
	std::vector<int> enemy_ids;
	while (e_iss.good()) {
		int temp_int;
		e_iss >> temp_int;
		enemy_ids.push_back(temp_int);
	}

	// Create enemy_spawns
	std::string spawn_amount = Read_Stream_To_Character(iss, ']', '[');
	replace(spawn_amount.begin(), spawn_amount.end(), ',', ' ');
	std::istringstream s_iss(spawn_amount);
	std::vector<Spawn_Amount*> enemy_spawns;
	while (s_iss.good()) {
		std::string temp_string;
		s_iss >> temp_string;
		replace(temp_string.begin(), temp_string.end(), '/', ' ');
		std::istringstream temp_iss(temp_string);
		int temp_min, temp_max;
		temp_iss >> temp_min >> temp_max;
		enemy_spawns.push_back(new Spawn_Amount{ temp_min, temp_max });
	}

	// create chance
	float chance;
	// std::string temp;
	// iss >> temp;
	iss >> chance;

	// Return a new encounter
	return new Encounter{ enemy_ids, enemy_spawns, chance };

}

std::string Encounter_Generator::Read_Stream_To_Character(std::istringstream& iss, char end_char,
	char ignore_char) {
	char temp_char;
	std::string s;
	while (iss >> std::noskipws >> temp_char) {
		if (temp_char == end_char) {
			// Read 1 past last character
			iss >> temp_char;
			// Return s[1:]
			return s;
		}
		if (temp_char != ignore_char)
			s += temp_char;
	}

	std::cout << "Read_Stream_To_Character to failed";
	exit(1);
}

void Encounter_Generator::Instantiate_Possible_Encounters(int area_id) {
	// Open encounters.txt
	std::ifstream inFS;
	inFS.open(ENCOUNTERS_FILE_LOC, std::ofstream::out | std::ofstream::app);
	std::string line, name;

	// Skip first line which is just the headers
	std::getline(inFS, line);
	// Return id if area name matches line found in file
	while (std::getline(inFS, line)) {
		replace(line.begin(), line.end(), ',', ' ');
		std::istringstream iss(line);
		int enc_id, area;
		// Read in second number as id
		iss >> enc_id >> area;
		// If area_id matches Encounter, add to possible_encounters
		if (area == area_id) {
			possible_encounters.push_back(Create_Encounter(iss));
		}
		else if (area > area_id) {
			break;
		}
	}

	inFS.close();
	
	if (possible_encounters.size() == 0) {
		std::cout << "Area ID not found in encounters.txt. Exiting.";
		exit(1);
	}

	return;
}

Encounter* Encounter_Generator::Roll_Encounter() {
	
	// Create vector of chances based on current probabilities of possible encounters
	std::vector<float> chances;
	float total = 0;
	int possible_encounter_size = possible_encounters.size();
	for (int i = possible_encounter_size - 1; i >= 0; i--) {
		total += possible_encounters.at(i)->chance;
		chances.push_back(total);
	}

	// Roll a random float between 0 and 100.0
	float roll = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 100.0;
	// Return a possible encounter based on the random roll
	for (int i = 0; i < possible_encounter_size; i++) {
		if (roll < chances.at(i))
			return possible_encounters.at(i);
	}

	return possible_encounters.at(0);
}

int Encounter_Generator::Roll_Spawn_Amount(Spawn_Amount* s_a) {
	if (s_a->max == 1 && s_a->min == 1)
		return 1;
	return rand() % (s_a->max - s_a->min) + s_a->min;
}

std::vector<Creature*> Encounter_Generator::Instantiate_Encounter_Enemies() {
	// Go through current_encounter
	int vector_size = current_encounter->enemy_ids.size();
	int encounter_total = 0;
	// Create Creature*
	for (int i = 0; i < vector_size; i++) {
		// Roll for how many of this enemy_id to create
		int spawn_amount = Roll_Spawn_Amount(current_encounter->enemy_spawns.at(i));
		// If the number of spawned enemies is less than the total possible
		if ((encounter_total + spawn_amount) <= TOTAL_ENEMIES) {
			// Spawn that number of Creature* and store in encounter_enemies
			for (int j = 0; j < spawn_amount; j++) {
				// Generate Enemy based on their id and current place in battle with encounter_total
				encounter_enemies.push_back(
					E_G->Generate_Enemy(current_encounter->enemy_ids.at(i), encounter_total));
				encounter_total++;
			}
		}
	}

	return encounter_enemies;
}

Encounter_Generator::Encounter_Generator() {
	E_G = new Enemy_Generator();
	current_encounter = nullptr;
}

// Destructor to free dynamic memory
Encounter_Generator::~Encounter_Generator() {

	for (Encounter* e : possible_encounters) {
		delete e;
		e = nullptr;
	}
	possible_encounters.clear();

	current_encounter = nullptr;

	for (Creature* e : encounter_enemies) {
		delete e;
		e = nullptr;
	}
	encounter_enemies.clear();

}

// Beefy boy that does all the work
std::vector<Creature*> Encounter_Generator::Spawn_Encounter(std::string area_name) {
	// Might need a function to reset all local variables for new encounter
	int area_id = Area_Name_To_ID(area_name);
	Instantiate_Possible_Encounters(area_id);
	current_encounter = Roll_Encounter();

	return Instantiate_Encounter_Enemies();
}


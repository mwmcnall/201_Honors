#include "Enemy_Generator.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <sstream> 

Enemy_Generator::Enemy_Generator() : enemy(nullptr){}

Enemy_Generator::~Enemy_Generator() {
	delete enemy;
}

Enemy* Enemy_Generator::Generate_Enemy(const std::string enemy_name, const int turn_id) {
	if (turn_id < 0 || turn_id > 8) {
		std::cout << "ERROR: Enemy must be generated with a turn id between 0 and 8";
		exit(1);
	}

	// Open the file
	std::ifstream inFS;
	inFS.open(ENEMY_FILE_LOC, std::ofstream::out | std::ofstream::app);

	std::string line, name;
	// Skip first line which is just the headers
	std::getline(inFS, line);

	while (std::getline(inFS, line)) {
		// Replace commas with spaces for easier reading
		replace(line.begin(), line.end(), ',', ' ');
		std::istringstream iss(line);
		int id;
		iss >> id;
		// If you can't read a string from the line, end of file, break loop
		if (!(iss >> name))
			break;
		if (name == enemy_name) {
			int hit_perc, hp, attack, defense, mag_defense, eva_perc, exp, gil, hits;
			iss >> hit_perc >> hp >> attack >> defense >> mag_defense >> eva_perc >> exp >> gil >> hits;
			enemy = new Enemy(enemy_name, id, hit_perc, hp, attack, defense, mag_defense, eva_perc, exp, turn_id,
				gil, hits);
			inFS.close();
			return enemy;
		}
	}

	inFS.close();

	// Enemy name not found, return null pointer
	return nullptr;
}

Enemy* Enemy_Generator::Generate_Enemy(const int enemy_id, const int turn_id) {
	if (turn_id < 0 || turn_id > 8) {
		std::cout << "ERROR: Enemy must be generated with a turn id between 0 and 8";
		exit(1);
	}

	// Open the file
	std::ifstream inFS;
	inFS.open(ENEMY_FILE_LOC, std::ofstream::out | std::ofstream::app);

	std::string line, name;
	// Skip first line which is just the headers
	std::getline(inFS, line);

	while (std::getline(inFS, line)) {
		// Replace commas with spaces for easier reading
		replace(line.begin(), line.end(), ',', ' ');
		std::istringstream iss(line);
		int id;
		iss >> id;
		// If you can't read a string from the line, end of file, break loop
		if (id == enemy_id) {
			int hit_perc, hp, attack, defense, mag_defense, eva_perc, exp, gil, hits;
			iss >> name >> hit_perc >> hp >> attack >> defense >> mag_defense >> eva_perc >> exp >> gil >> hits;
			enemy = new Enemy(name, id, hit_perc, hp, attack, defense, mag_defense, eva_perc, exp, turn_id,
				gil, hits);
			inFS.close();
			return enemy;
		}
	}

	inFS.close();

	// Enemy name not found, return null pointer
	return nullptr;
}
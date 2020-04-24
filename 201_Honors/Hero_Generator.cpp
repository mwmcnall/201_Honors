#include "Hero_Generator.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <sstream> 

Hero_Generator::Hero_Generator() : hero(nullptr) {}

Hero_Generator::~Hero_Generator() {
	if (hero != nullptr)
		delete hero;
	hero = nullptr;
}

Hero* Hero_Generator::Generate_Hero(const std::string hero_name, const int turn_id) {
	if (turn_id < 80 || turn_id > 83) {
		std::cout << "ERROR: Hero must be generated with a turn id between 80 and 83";
		exit(1);
	}

	// Open the file
	std::ifstream inFS;
	inFS.open(HERO_FILE_LOC, std::ofstream::out | std::ofstream::app);

	std::string line, name;
	// Skip first line which is just the headers
	std::getline(inFS, line);

	while (std::getline(inFS, line)) {
		// Replace commas with spaces for easier reading
		replace(line.begin(), line.end(), ',', ' ');
		std::stringstream iss(line);
		// If you can't read a string from the line, end of file, break loop
		if (!(iss >> name))
			break;
		if (name == hero_name) {
			int hit_perc, hp, mag_defense, str, agi, inte, vit, luck, job;
			iss >> hit_perc >> hp >> mag_defense >> str >> agi >> inte >> vit >> luck >> job;
			hero = new Hero(hero_name, hit_perc, hp, 0, 0, mag_defense, 0, 0, turn_id,
				str, agi, inte, vit, luck, 0, job);
			inFS.close();
			return hero;
		}
	}

	inFS.close();

	// Hero name not found, return null pointer
	return nullptr;
}
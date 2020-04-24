#include "Generator.h"

template <class T>
Generator<T>::Generator() : creature_pointer(nullptr) {}

Generator<Enemy>::Generator() : creature_pointer(nullptr) {
	TURN_ID_LOWER_LIMIT = 0;
	TURN_ID_UPPER_LIMIT = 8;
	FILE_LOC = "./data/enemies.txt";
}

Generator<Hero>::Generator() : creature_pointer(nullptr) {
	TURN_ID_LOWER_LIMIT = 80;
	TURN_ID_UPPER_LIMIT = 83;
	FILE_LOC = "./data/heroes.txt";
}

Generator<Enemy>::~Generator() {
	delete creature_pointer;
}

Generator<Hero>::~Generator() {
	delete creature_pointer;
}

template <class T>
Generator<T>::~Generator() {
	delete creature_pointer;
}

template <class T>
Enemy* Generator<T>::Instantiate_Creature(Enemy* enemy, std::string enemy_name, std::istringstream iss, const int turn_id) {
	int hit_perc, hp, attack, defense, mag_defense, eva_perc, exp, eva, acc, gil;
	iss >> hit_perc >> hp >> attack >> defense >> mag_defense >> eva_perc >> exp >> eva >> acc >> gil;
	enemy = new Enemy(enemy_name, hit_perc, hp, attack, defense, mag_defense, eva_perc, exp, turn_id,
		eva, acc, gil);
	return enemy;
}
/*
template <class T>
T* Generator<T>::Instantiate_Creature(Hero* hero, std::string hero_name, std::istringstream iss, const int turn_id) {
	int hit_perc, hp, attack, defense, mag_defense, eva_perc, exp, str, agi, inte, vit, luck, eva, job;
	iss >> hit_perc >> hp >> attack >> defense >> mag_defense >> eva_perc >> exp >> str >> agi >> inte >> vit >> luck >> eva >> job;
	hero = new Hero(hero_name, hit_perc, hp, attack, defense, mag_defense, eva_perc, exp, turn_id,
		str, agi, inte, vit, luck, eva, job);
	return hero;
}
*/

template <class T>
T* Generator<T>::Generate(const std::string creature_name, const int turn_id) {
	if (turn_id < TURN_ID_LOWER_LIMIT || turn_id > TURN_ID_UPPER_LIMIT) {
		std::cout << "ERROR: This Creature must be generated with a turn id between " << TURN_ID_LOWER_LIMIT << " and " << TURN_ID_UPPER_LIMIT;
		exit(1);
	}

	// Open the file
	std::ifstream inFS;
	inFS.open(FILE_LOC, std::ofstream::out | std::ofstream::app);

	std::string line, name;
	// Skip first line which is just the headers
	std::getline(inFS, line);

	while (std::getline(inFS, line)) {
		std::istringstream iss(line);
		// If you can't read a string from the line, end of file, break loop
		if (!(iss >> name))
			break;
		if (name == creature_name) {
			T* temp_pointer = nullptr;
			creature_pointer = Instantiate_Creature(temp_pointer, creature_name, iss, turn_id);
			inFS.close();
			return creature_pointer;
		}
	}

	inFS.close();

	// name not found, return null pointer
	return nullptr;
}
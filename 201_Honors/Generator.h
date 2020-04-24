#ifndef GEN_H
#define GEN_H

#pragma once
// Might need to create a generic class Hero / Enemy object for the build phase
#include "Enemy.h"
#include "Hero.h"
//#include "Creature.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <sstream> 


template <class T>
class Generator
{
private: // Variables
	T* creature_pointer;
	int TURN_ID_LOWER_LIMIT, TURN_ID_UPPER_LIMIT;
	std::string FILE_LOC;
private:
	Enemy* Instantiate_Creature(Enemy* enemy, std::string enemy_name, std::istringstream iss,
		const int turn_id);
	/*
	T* Instantiate_Creature(Hero* hero, std::string hero_name, std::istringstream iss,
		const int turn_id);
		*/
public:
	Generator();
	~Generator();

	T* Generate(const std::string creature_name, const int turn_id);
};

#endif
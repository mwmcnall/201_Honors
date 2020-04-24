#ifndef HERO_GEN_H
#define HERO_GEN_H

#pragma once
#include "Hero.h"

const std::string HERO_FILE_LOC = "./data/heroes.txt";

class Hero_Generator {
private: // Variables
	Hero* hero;
private: // Methods

public: // Methods
	// Constructor
	Hero_Generator();
	~Hero_Generator();

	void Set_Hero(Hero* hero) { this->hero = hero; };

	// Methods
	Hero* Generate_Hero(const std::string hero_name, const int turn_id);
};

#endif
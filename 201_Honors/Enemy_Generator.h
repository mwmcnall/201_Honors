#ifndef ENEMY_GEN_H
#define ENEMY_GEN_H

#pragma once
#include "Enemy.h"

const std::string ENEMY_FILE_LOC = "./data/enemies.txt";

class Enemy_Generator {
private: // Variables
	Enemy* enemy;
private: // Methods
	
public: // Methods
	// Constructor
	Enemy_Generator();
	~Enemy_Generator();

	void Set_Enemy(Enemy* enemy) { this->enemy = enemy; }

	// Methods
	Enemy* Generate_Enemy(const std::string enemy_name, const int turn_id);
	Enemy* Generate_Enemy(const int enemy_id, const int turn_id);
};

#endif
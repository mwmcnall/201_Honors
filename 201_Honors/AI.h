#pragma once
#ifndef AI_H
#define AI_H

#include "Battle.h"

class AI
{
public: // Variables
	static Battle battle;

public: // Methods
	Creature* Choose_Target();
	Creature* Target_Slot(unsigned int slot);
	Creature* Target_Strongest();
	Creature* Target_Weakest();
	Creature* Choose_Lowest_HP_Target();
};

#endif
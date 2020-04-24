#pragma once
#ifndef PARTY_GEN_H
#define PARTY_GEN_H

#include <vector>
#include "Hero.h"
#include "Hero_Generator.h"

class Party_Generator
{	
private:
	Hero_Generator* H_G;
	std::vector<Creature*> party;
public:
	Party_Generator();
	~Party_Generator();

	std::vector<Creature*> Create_Party(std::string class_1, std::string class_2,
		std::string class_3, std::string class_4, int turn_id_1 = 80, int turn_id_2 = 81, 
		int turn_id_3 = 82, int turn_id_4 = 83);
};

#endif
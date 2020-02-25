#pragma once
#ifndef ARMOR_H
#define ARMOR_H

#include "Equipment.h"
class Armor :
	public Equipment
{
public:
	unsigned int defense = 0, weight = 0;
	Armor();
	Armor(unsigned int p_defense, unsigned int p_weight);
};

#endif
#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include "Equipment.h"
class Weapon :
	public Equipment 
{
private:
	// TODO: static const enum for types
public:
	unsigned int attack = 0, crit_rate = 0, type = 0;
	Weapon();
	Weapon(unsigned int p_attack, unsigned int p_crit_rate, unsigned int p_type);
};

#endif
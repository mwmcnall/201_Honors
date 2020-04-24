#pragma once
#ifndef EQUIP_H
#define EQUIP_H

#include "Creature.h"
class Equipment
{
protected:
	// TODO: const static enum for element affinity
	// TODO: const static enum for job class
public:
	Equipment();
	void Change_Equipment(Creature* target);
};
#endif
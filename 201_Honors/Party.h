#pragma once
#ifndef PARTY_H
#define PARTY_H

#include "Item.h"
#include <vector>
class Party
{
public:
	// TODO: Determine item size limite
	std::vector<Item> items;
public:
	Party();
};

#endif
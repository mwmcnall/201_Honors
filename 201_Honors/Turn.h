#pragma once
#ifndef TURN_H
#define TURN_H
#include <stdlib.h>
#include <vector>
class Turn
{
private:
	unsigned int turn = 1;
protected:
	const static std::vector<unsigned int> turn_IDs;
protected:
	void Swap_Positions(std::vector<unsigned int>& vec, unsigned int pos1, unsigned int pos2);
public:
	Turn();
	unsigned int Get_Turn() { return turn; }
	void Set_Turn(unsigned int turn) { this->turn = turn; }
};

#endif
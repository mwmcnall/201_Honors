#include "Turn.h"

Turn::Turn(){};

const std::vector<unsigned int> Turn::turn_IDs = {0, 1, 2, 3, 4, 5, 6,
	                                              7, 8, 80, 81, 82, 83};

// Swap two positions of a vector
void Turn::Swap_Positions(std::vector<unsigned int>& vec, unsigned int pos1, unsigned int pos2) {
    unsigned int temp = vec.at(pos1);
    vec.at(pos1) = vec.at(pos2);
    vec.at(pos2) = temp;

    return;
}
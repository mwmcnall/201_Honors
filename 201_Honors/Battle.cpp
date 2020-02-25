#include "Battle.h"

Battle::Battle() : Round(), victor(""), current_target_ID(-1){
	// Start_Battle();
}

Creature* Battle::Participant_From_ID(unsigned int target_id) {
	for (int i = 0; i < static_cast<int>(participants.size()); i++) {
		// If current turn ID is in participants_ID, meaning they are part of the battle
		if (participants.at(i)->turn_ID == target_id) {
			return participants.at(i);
		}

	}
}
#include "Party_Generator.h"

Party_Generator::Party_Generator() {
	H_G = new Hero_Generator();
}

Party_Generator::~Party_Generator() {
	for (Creature* p : party) {
		delete p;
	}
	party.clear();

	H_G->Set_Hero(nullptr);
	delete H_G;
	H_G = nullptr;
}

std::vector<Creature*> Party_Generator::Create_Party(std::string class_1, std::string class_2,
	std::string class_3, std::string class_4, int turn_id_1, int turn_id_2,
	int turn_id_3, int turn_id_4) {
	// Create a player of each of those types and add it to the vector
	std::vector<std::string> player_classes = { class_1 , class_2, class_3, class_4};
	std::vector<int> player_turn_ids = { turn_id_1 , turn_id_2, turn_id_3, turn_id_4 };

	for (int i = 0; i < static_cast<int>(player_classes.size()); i++) {
		party.push_back(H_G->Generate_Hero(player_classes.at(i), player_turn_ids.at(i)));
	}

	return party;
}
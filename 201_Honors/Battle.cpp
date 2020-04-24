#include "Battle.h"

Battle::Battle() : Round(), current_target_ID(-1){
	// Start_Battle();
}

Battle::Battle(std::vector<Creature*> participants) : Round{participants}, current_target_ID(-1) {
    
}

// Writes a given string vector to an output file stream
void Battle::Write_Vector_To_File(std::ofstream& outFS, std::vector<std::string> vec) {

    // Wraps the array in quotes, making it easier to read from the file 
    // as it defines boundaries to the vector
    outFS << "\"";

    int vec_size = static_cast<int>(vec.size());

    for (int i = 0; i < vec_size; i++) {
        outFS << vec.at(i);
        // Only have spaces between elements, not at the end
        if (i != vec_size - 1)
            outFS << " ";
    }

    outFS << "\"";

    outFS << ",";

}

// Writes new information to battle_result.txt
void Battle::Update_Battle_Result(Battle_Result* b_r) {

    // Open file
    std::ofstream outFS;
    std::string file_path = "./data/battle_result.txt";
    outFS.open(file_path, std::ofstream::out | std::ofstream::app);

    // Add new information to file
    outFS << this->b_r_id << ",";
    Write_Vector_To_File(outFS, b_r->enemy_names);
    Write_Vector_To_File(outFS, b_r->hero_names);
    outFS << b_r->round_tot << ",";
    outFS << b_r->turn_tot << ",";
    outFS << b_r->victor << ",";
    outFS << b_r->hp_loss_victor << ",";
    outFS << this->b_h_id << std::endl;

    // Close file
    outFS.close();

    return;
}

// TODO: Finish writing this function and add it to Battle.h
void Add_HP_Loss(Battle_Result* b_r, Battle_History* turn, std::vector<std::string> vec) {
    if (std::find(vec.begin(), vec.end(), turn->target_name) != vec.end()) {
        b_r->hp_loss_victor += turn->action_result;
    }

    return;
}

void Battle::Start_Battle() {

    // To store the result of each turn to reference later
    std::vector<Battle_History*> turn_results;

    // Create a new battle result
    Battle_Result* b_r = new Battle_Result;

    // Fill names for battle_result before battle begins
    for (Creature* enem : participant_enemies) {
        b_r->enemy_names.push_back( enem->name );
    }
    for (Creature* hero : participant_heroes) {
        b_r->hero_names.push_back(hero->name);
    }

    while (1 == 1) {
        // If the round signifies battle is over, end battle
        if (!this->Battle_Round(turn_results))
            break;
        this->Set_Rounds(this->Get_Rounds() + 1);
        // Debug condition to help prevent infinite loops
        /*
        if (this->Get_Rounds() > 10)
            break;
        */
    }

    // Update battle_result after fight
    b_r->round_tot = this->Get_Rounds();
    b_r->turn_tot = this->Get_Turn();
    b_r->victor = this->Get_Victor();
    b_r->hp_loss_victor = 0;
    for (Battle_History* turn : turn_results) {
        // If target name matches the list of victor names
        // And the action was an attack
        // Then add that to the hp lost

        // If action was attack
        if (turn->attack_type == "attack") {
            // Look at target name and determine if target is a hero or an enemy
            if (b_r->victor == "Heroes") {
                Add_HP_Loss(b_r, turn, b_r->hero_names);
            }
            else {
                Add_HP_Loss(b_r, turn, b_r->enemy_names);
            }
        }
    }

    this->Update_Battle_Result(b_r);

    // Clear dynamic memory
    delete b_r;
    // TODO: Need to clear dynamic memory of the turn_results
    return;
}

/*
Old python code for reference

def battle(self):
        assert len(self.participants) > 0, \
            "participants should be a list of all Enemies and Characters"
        while 1 == 1:
            if not self.battle_round():
                break
            self.rounds += 1
            # Debug condition
            if self.rounds >= 10:
                break
        self._update_battle_result()
        return
*/
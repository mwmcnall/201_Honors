#include "Round.h"
#include <conio.h>
#include <algorithm>
#include <sstream> 

// Creates file in the ./data/ folder if it doesn't exist yet
// Returns true if created, false if already exists.
bool Round::Create_File_If_Not_Exists(const std::string file_name) {
    FILE* file;
    bool created;

    // .c_str() is used to conver the string variable into a char *
    file = fopen(file_name.c_str(), "r");

    // Creates file if it doesn't exist yet
    if (file == NULL) {
        file = fopen(file_name.c_str(), "w+");
        created = true;
    }
    else
        created = false;

    fclose(file);

    return created;
}

// If the file hasn't been created yet, create it with the data columns in .csv format
void Round::Initialize_Data_File_Columns(const std::string file_name, 
    const std::vector<std::string> file_cols) {

    bool created;
    std::ofstream outFS;

    const std::string file_path = "./data/" + file_name;

    created = Create_File_If_Not_Exists(file_path);

    // If file is newly created
    if (created) {
        // Open file as ofstream to output to it
        outFS.open(file_path, std::ofstream::out | std::ofstream::app);

        std::string temp;

        // Write all column names to file to initialize battle_history.txt
        for (int i = 0; i < static_cast<int>(file_cols.size()); i++) {
            temp = file_cols.at(i);
            outFS << file_cols.at(i);
            // Put commas after every header but the last one
            if (i <= static_cast<int>(file_cols.size()) - 2)
                outFS << ",";
        }

        outFS << std::endl;

        outFS.close();
    }
    // Otherwise do nothing and return
    return;

}

// Converts Creature* participants to their unsigned int turn_IDs stored in a vector
void Round::Initialize_Participant_Turn_IDs() {
    for (int i = 0; i < static_cast<int>(participants.size()); i++) {
        participant_IDs.push_back(participants.at(i)->turn_ID);
    }
    return;
}

// Initializes vector of Enemies
std::vector<Creature*> Round::Subset_Enemies() {

    std::vector<Creature*> temp;

    for (Creature* itr : participants) {
        if (itr->turn_ID < 10)
            temp.push_back(itr);
    }

    return temp;
}

// Initializes vector of Heroes
std::vector<Creature*> Round::Subset_Heroes() {
    std::vector<Creature*> temp;

    for (Creature* itr : participants) {
        if (itr->turn_ID >= 80)
            temp.push_back(itr);
    }

    return temp;
}

// Initializes round, used for both with and without valued constructor
void Round::Initialize_Round() {
    this->Initialize_Participant_Turn_IDs();
    Initialize_Data_File_Columns("battle_history.txt", Round::battle_history_cols);
    Initialize_Data_File_Columns("battle_result.txt", Round::battle_result_cols);
    // Set b_h_id and b_r_id;
    b_h_id = Get_Data_Entry_ID("./data/battle_history.txt");
    b_r_id = Get_Data_Entry_ID("./data/battle_result.txt");
    // Initialize participant_enemies / participant_heroes
    participant_enemies = Subset_Enemies();
    participant_heroes = Subset_Heroes();
}

// Deafult Constructor
Round::Round()
    : rounds(1) {
    std::vector<Creature*> p_participants;
    this->participants = p_participants;
    Initialize_Round();
}

// Valued Constructor
Round::Round(std::vector<Creature*> participants)
	: rounds(1), participants(participants){
    Initialize_Round();
}

// https://www.sanfoundry.com/cpp-program-count-lines-in-file/
// Helper function, not in Round.h as I don't expect to reuse it anywhere else
unsigned int Get_File_Line_Count(const std::string file_name) {
    int count = 0;
    std::string line;

    /* Creating input filestream */
    std::ifstream file(file_name);
    while (getline(file, line))
        count++;

    return count;
}

// http://www.programmersbook.com/page/7/Get-last-line-from-a-file-in-C/
// Returns the last line in a file
std::string Get_Last_Line_Of_File(const std::string file_name) {
    std::ifstream read(file_name, std::ios_base::ate);//open file
    std::string tmp;
    int length = 0;
    int return_count = 0;

    char c = '\0';

    if (read)
    {
        length = read.tellg();//Get file size

        // loop backward over the file

        for (int i = length - 2; i > 0; i--)
        {
            read.seekg(i);
            c = read.get();
            if (c == '\r' || c == '\n') {
                return_count++;
                if (return_count >= 2)
                    break;
            }
        }

        std::getline(read, tmp);//read last line
        return tmp;
    }

    return "";
}

// Gets the current ID entry from a particular file to store
// Necessary if updating document that has already been filled with data
unsigned int Round::Get_Data_Entry_ID(std::string file_name) {

    int num_lines = Get_File_Line_Count(file_name);
    
    // If file has only been initialied with column headers; no data
    if (num_lines == 1)
        return 1;
    else { // If file has had information written to it
        std::string last_line = Get_Last_Line_Of_File(file_name);
        // Return first integer of line, which represents the battle history id
        std::stringstream ss;
        ss << last_line;
        int temp;
        ss >> temp;
        return temp + 1;
    }

}

// Writes new information to battle_history.txt
void Round::Update_Battle_History(Battle_History* b_h) {

    // Open file
    std::ofstream outFS;
    std::string file_path = "./data/battle_history.txt";
    outFS.open(file_path, std::ofstream::out | std::ofstream::app);

    // Add new information to file
    outFS << this->b_h_id<< ",";
    outFS << b_h->round << ",";
    outFS << b_h->turn << ",";
    outFS << b_h->turn_id << ",";
    outFS << b_h->self_name << ",";
    outFS << b_h->target_name << ",";
    outFS << b_h->attack_type << ",";
    outFS << b_h->action_result << std::endl;

    // Close file
    outFS.close();

    return;
}

// Set new Creature* target
void Round::Set_Current_Target(Creature* new_target) {
    this->target = new_target;
}

// Returns true if target was defeated
bool Round::Target_Defeated() {
    return target->If_Dead();
}

// Removes a Creature* from a given vector
void Round::Remove_Creature_From_Vector(std::vector<Creature*>& vec) {
    for (int i = 0; i < static_cast<int>(vec.size()); i++) {
        if (target == vec.at(i)) {
            vec.erase(vec.begin() + i);
        }
    }
}

// Removes the target's turn id from the participant_ID vector
void Round::Remove_Participant_ID() {
    for (int i = 0; i < static_cast<int>(participant_IDs.size()); i++) {
        if (target->turn_ID == participant_IDs.at(i)) {
            participant_IDs.erase(participant_IDs.begin() + i);
        }
    }
    return;
}

// If target is dead, remove from corresponding vectors
void Round::Remove_Participant() {

    Remove_Creature_From_Vector(participants);
    Remove_Participant_ID();

    // Remove Hero
    if (target->turn_ID >= 80) {
        Remove_Creature_From_Vector(participant_heroes);
    }
    // Remove Enemy
    else {
        Remove_Creature_From_Vector(participant_enemies);
    }

    target = nullptr;

    return;
}

// Returns true if battle round signifies the end of battle
// Returns false if battle should continue
bool Round::End_Condition() {
    // A battle is over if all heroes or all participants are dead
    if (static_cast<int>(participant_enemies.size()) == 0) {
        Set_Victor("Heroes");
        return true;
    }
    else if (static_cast<int>(participant_heroes.size()) == 0) {
        Set_Victor("Enemies");
        return true;
    }
    else
        return false;
}

// Returns the index of a turn id within participant_IDs
int Round::Index_Of_Turn_ID(int value) {
    int index = 0;
    for (int turn_id : this->participant_IDs) {
        if (value == turn_id)
            return index;
        index++;
    }
    // Not found
    return -1;
}

// Logic for a single round of combat
bool Round::Battle_Round(std::vector<Battle_History*>& turn_results) {

    // Loop through turn_IDs, this represents the turn order
    for (unsigned int itr : this->turn_IDs){
        // If the current turn_ID is alive and in battle, then have them go
        if (std::find(participant_IDs.begin(), participant_IDs.end(), itr) != participant_IDs.end()) {
            // Grab class associated with current turn ID
            Creature* turn_class = participants.at(Index_Of_Turn_ID(itr));
            // Run AI turn, this will trigger either Enemy or Hero's override of AI_Turn
            Battle_History* b_h = turn_class->AI_Turn(this);
            // Update turn that just happened in the master list to reference later
            turn_results.push_back(b_h);
            // Write turn to file
            Update_Battle_History(b_h);
            // Set current target
            this->Set_Current_Target(b_h->target);
            
            // If target was defeated after turn
            if (this->Target_Defeated()) {
                this->Remove_Participant();
                if (this->End_Condition()) {
                    return false;
                }
                continue;
            }
            Set_Turn( Get_Turn() + 1 );
        }

    }

    return true;

}

// Returns Creature pointer from participants based on turn id
Creature* Round::Participant_From_ID(unsigned int target_id) {
    for (int i = 0; i < static_cast<int>(participants.size()); i++) {
        // If current turn ID is in participants_ID, meaning they are part of the battle
        if (participants.at(i)->turn_ID == target_id) {
            return participants.at(i);
        }
    }
}
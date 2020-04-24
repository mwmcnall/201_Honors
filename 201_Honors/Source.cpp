
#include "Encounter_Generator.h"
#include "Party_Generator.h"
#include "Enemy_Generator.h"
#include "Hero_Generator.h"
#include "Battle.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <time.h>
using namespace std;

// Returns a combined vector of two separate Creature* vectors
vector<Creature*> Combine_Creatures(vector<Creature*> v1, vector<Creature*> v2) {
    v1.insert(v1.end(), v2.begin(), v2.end());
    return v1;
}

// https://www.techiedelight.com/print-vector-cpp/
// Output the contents of an int vector, for debugging
void print(vector<int> const& input) {
    copy(input.begin(),
        input.end(),
        ostream_iterator<int>(cout, " "));
    cout << endl;
}

const int SIM_NUMBER = 10;
const string LOCATION = "North of Coneria";

int main(int argc, char** argv) {

    // Set random seed
    srand(time(NULL));

    // Simulate a number of battles
    for (int i = 0; i < SIM_NUMBER; i++) {
        // Create Party and Encounter generators
        Party_Generator* Party_Gen = new Party_Generator();
        Encounter_Generator* Enc_Gen = new Encounter_Generator();

        // Instantiate party and encounter
        vector<Creature*> party = Party_Gen->Create_Party("Fighter", "Black_Belt",
            "White_Mage", "Black_Mage");
        vector<Creature*> encounter = Enc_Gen->Spawn_Encounter(LOCATION);

        // Instantiate a battle complete with all Heroes and Enemies
        Battle battle(Combine_Creatures(party, encounter));
        // Simulate battle
        battle.Start_Battle();

        // Clear to reset
        encounter.clear();
        delete Party_Gen;
        delete Enc_Gen;
    }
    
	return 0;
}


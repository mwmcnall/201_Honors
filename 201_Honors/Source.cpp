
#include "Hero.h"
#include "Enemy.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <time.h>
using namespace std;


void turn_order(vector<int>& turn_ids) {
    for (int i = 0; i < 17; i++) {
        //swap_positions(turn_ids, rand() % 13, rand() % 13);
    }
}

// https://www.techiedelight.com/print-vector-cpp/
void print(vector<int> const& input) {
    copy(input.begin(),
        input.end(),
        ostream_iterator<int>(cout, " "));
    cout << endl;
}


int main(int argc, char** argv) {

    Round round;

    /*
    std::string test_string = "Imp";
    int test_hit_perc = 85;
    unsigned int testHP = 8, test_attack = 6, test_defense = 4, test_mag_defense = 8,
        test_eva_perc = 3, test_exp = 6, test_turn_id = 0, test_eva = 0,
        test_acc = 0, test_gil = 6;
    Enemy enemy(test_string, test_hit_perc, testHP, test_attack, test_defense,
        test_mag_defense, test_eva_perc, test_exp, test_turn_id, test_eva,
        test_acc, test_gil);

    cout << enemy.name << endl;

    */

	return 0;
}


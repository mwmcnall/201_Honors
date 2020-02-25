#include "Enemy.h"
#include "Hero.h"
#include <cstdlib>

// Default Constructor
Enemy::Enemy() : Creature(), eva(0), acc(0), gil(0){}

// Variable Constructor
Enemy::Enemy(std::string p_name, unsigned int p_hitPerc,
    unsigned int p_hp, unsigned int p_attack, unsigned int p_defense, unsigned int p_mag_defense,
    unsigned int p_eva_perc, unsigned int p_exp, unsigned int p_turn_id,
    unsigned int p_eva, unsigned int p_acc, unsigned int p_gil)
    : Creature(p_name, p_hitPerc, p_hp, p_attack, p_defense, p_mag_defense,
               p_eva_perc, p_exp, p_turn_id), eva(p_eva), acc(p_acc), gil(p_gil) {}

unsigned int Enemy::Target_Slot(unsigned int slot) {
    if (slot <= 4)
        return 80;
    else if (slot <= 6)
        return 81;
    else if (slot == 7)
        return 82;
    return 83;
}

unsigned int Enemy::Choose_Target() {
    // Generates a number 1-8, this determines that enemy's target
    int rand_target;
    unsigned int target_id;
    while (1 == 1) {
        // 1 to 8
        rand_target = (rand() % 8) + 1;
        target_id = Target_Slot(rand_target);
        // if target_id is in battle
        if (std::find(battle->participant_IDs.begin(), battle->participant_IDs.end(), target_id) != battle->participant_IDs.end()) {

        }
        // TODO: Check if target_id is in the battle
        // If so, return that target id
        // Otherwise keep generating Ids
    }
}

Battle_History* Enemy::AI_Turn() {

    // Get target id and actual target
    unsigned int target_id = Choose_Target();
    Creature* target = battle->Participant_From_ID(target_id);

    unsigned int damage = this->Attack_Target(target);

    // TODO: Currently only 'attack' is implemented
    Battle_History b_h = { battle->rounds, battle->Get_Turn(),
        this->name, target->name, "attack", damage };

    // TODO: Check scope of this, see if the data of b_h disappears upon runnings
    return &b_h;

    /*
    # TODO: Determine if enemy runs
    # Morale - 2*[Leader's Level] + (0..50) < 80
    # TODO: If spell AI: choose a number 0..128 if that number is equal to
    # or less than the spell chance for that enemy, cast a spell. If not
    # check for skills
    # TODO: If skill AI: choose a number 0..128 if that number is equal to
    # or less than the skill chance for that enemy, use a skill
    # If the enemy decies to use a skill or spell, it uses the next one in
    # the list. It always egins with the first spell / skill and moves on
    # sequentially.


    # Just attack first enemy
    # target = list(battle.participants_heroes.values())[0]
    damage = self.attack_target(target)
    # Returns a list in this format:
    # ['round_num', 'turn_num', 'self_name', 'target_name', 'action',
    #  'action_result']
    # TODO: 'attack' and damage are hard-coded, this will need to be
    # changed once there is actually AI
    return {k:v for (k,v) in zip(battle._battle_history_cols,
        [battle.rounds, battle.turn, self.name, target.name, 'attack',
        damage])}, target.turn_id
    
    */
}
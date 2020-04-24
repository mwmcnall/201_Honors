#include "Hero.h"
// For debug purposes
#include <iostream>
#include <algorithm>

// All classes have the same exp level breakpoints 
const std::vector<unsigned int> Hero::expTable = {40, 196, 547, 1171, 2146, 3550, 5461, 7957, 11116,
        15016, 19735, 25351, 31942, 39586, 48361, 58345, 69617, 82253, 96332,
        111932, 129131, 148008, 168639, 191103, 215479, 241843, 270275, 300851,
        333651, 366450, 399250, 432049, 464849, 497648, 530448, 563247, 596047,
        628846, 661646, 694445, 727245, 760044, 792844, 825643, 858443, 891242,
        924042, 956841, 989641};

// Default Constructor
Hero::Hero() : Creature(), str(0), agi(0), inte(0), vit(0), luck(0), eva(0), lvl(1) {}

// Valued Constructor
Hero::Hero(std::string p_name, unsigned int p_hitPerc,
    unsigned int p_hp, unsigned int p_attack, unsigned int p_defense, unsigned int p_mag_defense,
    unsigned int p_eva_perc, unsigned int p_exp, unsigned int p_turn_id,
    unsigned int p_str, unsigned int p_agi, unsigned int p_inte, unsigned int p_vit,
    unsigned int p_luck, unsigned int p_eva, int p_job)
    : Creature(p_name, p_hitPerc, p_hp, p_attack, p_defense, p_mag_defense,
        p_eva_perc, p_exp, p_turn_id),
    str(p_str), agi(p_agi), inte(p_inte), vit(p_vit), luck(p_luck), eva(p_eva), lvl(1) {
        this->Set_Job(p_job);
        this->attack = Attack_Formula();
    }

// Sets value of attack for Hero, this is based on stats AND equipped weapon
unsigned int Hero::Attack_Formula() {

    unsigned int attack = 0;

    // If weapon attack is 0, then unnarmed And black belt or master
    if (this->weapon.attack == 0 && (job_class_vec.at(b_belt) || job_class_vec.at(master))) {      
        attack = this->Get_Lvl() * 2;
    }
    else {
        // Standard
        attack = this->weapon.attack + (this->Get_Str() / 2);
        if (job_class_vec.at(b_belt) || job_class_vec.at(master) || job_class_vec.at(b_mage) || job_class_vec.at(b_wiz))
            attack += 1;
    }

    // Note: Attack can *not* be higher than 255, which should be impossible
    if (attack > 255)
        return 255;
    return attack;
}

// Returns true if hero is ready to level
bool Hero::If_Level() {
    if (this->exp > expTable.at(this->lvl - 1)) {
        return true;
    }

    return false;
}

// Levels Hero
void Hero::Level_Up() {
    this->Set_Lvl(this->Get_Lvl() + 1);
    // TODO: Depending on the job class increase different statistics
}

// AI Turn for hero
Battle_History* Hero::AI_Turn(Round* round) {

    // Get the target of the first monster in the battle
    Creature* target = round->participant_enemies.at(0);

    unsigned int damage = this->Attack_Target(target);

    // TODO: Currently only 'attack' is implemented
    Battle_History* b_h = new Battle_History{ round->Get_Rounds(), round->Get_Turn(),
        this->turn_ID, this->name, target->name, "attack", damage, target };

    return b_h;
}
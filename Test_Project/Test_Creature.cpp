#include "pch.h"
#include "CppUnitTest.h"
#include "../201_Honors/Creature.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestCreature
{
	TEST_CLASS(TestCreature)
	{
	public:
		
		TEST_METHOD(Test_Creature_Init)
		{
			std::string test_string = "Imp";
			unsigned int test_hit_perc = 85, test_hp = 8, test_attack = 6, test_defense = 4, test_mag_defense = 8,
				test_eva_perc = 3, test_exp = 6, test_turn_id = 0;

			Creature creature(test_string, //name
				test_hit_perc, //hitPerc
				test_hp, //hp
				test_attack, //attack
				test_defense, //defense
				test_mag_defense, //magDefense
				test_eva_perc, //evaPerc
				test_exp, //exp
				test_turn_id);//turnID
			Assert::AreEqual(test_string, creature.name);
			Assert::AreEqual(test_hit_perc, creature.hit_perc);
			Assert::AreEqual(test_attack, creature.attack);
			Assert::AreEqual(test_defense, creature.defense);
			Assert::AreEqual(test_mag_defense, creature.mag_defense);
			Assert::AreEqual(test_eva_perc, creature.eva_perc);
			Assert::AreEqual(test_exp, creature.exp);
			Assert::AreEqual(test_turn_id, creature.turn_ID);

			// Tests if Status has been initialized to all false
			for (int i = 0; i < creature.NR_STATUSES; i++) {
				Assert::IsFalse(creature.status.at(i));
			}
			
		}


		// TODO: Test attack Target

		TEST_METHOD(Test_Lower_HP) {
			Creature creature("Test", 0, 10, 0, 0, 0, 0, 0, 0);
			creature.Lower_HP(5);
			Assert::AreEqual(static_cast<unsigned int>(5), creature.hp);
		}


		TEST_METHOD(Test_Gain_HP) {
			Creature creature("Test", 0, 10, 0, 0, 0, 0, 0, 0);
			creature.Lower_HP(5);
			creature.Gain_HP(5);
			Assert::AreEqual(static_cast<unsigned int>(10), creature.hp);
		}

		TEST_METHOD(Test_If_Dead) {
			Creature creature("Test", 0, 10, 0, 0, 0, 0, 0, 0);
			// Make sure they aren't dead
			Assert::IsFalse(creature.If_Dead());
			creature.hp -= 11;
			Assert::IsTrue(creature.If_Dead());
		}

		// Tests to see if this method returns a float between 0 and 1
		// Tests five times because the number generated is random
		TEST_METHOD(Test_Rand_Zero_One) {
			float rand;
			Creature creature;

			for (int i = 0; i < 5; i++) {
				rand = creature.Rand_Zero_One();
				Assert::IsTrue((rand >= 0.0) && (rand <= 1.0));
			}
		}

		TEST_METHOD(Test_Roll_Hit) {
			int hitroll;
			Creature creature("Test", 0, 10, 0, 0, 0, 0, 0, 0);
			Creature target("Test", 0, 10, 0, 0, 0, 0, 0, 0);

			for (int i = 0; i < 5; i++) {
				hitroll = creature.Roll_Hit(target);
				Assert::IsTrue((hitroll >= 0) && (hitroll <= 255));
			}
		}
	};
	
}

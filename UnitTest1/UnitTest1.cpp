#include "pch.h"
#include "CppUnitTest.h"
#include "../201_Honors/Creature.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, 1);

			std::string test_string = "Imp";
			int test_hit_perc = 85;
			unsigned int test_hp = 8, test_attack = 6, test_defense = 4, test_mag_defense = 8,
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
		}

	};
}

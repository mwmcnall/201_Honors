#include "pch.h"
#include "CppUnitTest.h"
#include "../201_Honors/Enemy.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestEnemy
{
	TEST_CLASS(TestEnemy)
	{
	public:
		
		TEST_METHOD(Test_Enemy_Init) {
			std::string test_string = "Imp";
			unsigned int test_hit_perc = 85, testHP = 8, test_attack = 6, test_defense = 4, test_mag_defense = 8,
				test_eva_perc = 3, test_exp = 6, test_turn_id = 0, test_eva = 0,
				test_acc = 0, test_gil = 6;
			Enemy enemy(test_string, test_hit_perc, testHP, test_attack, test_defense,
				test_mag_defense, test_eva_perc, test_exp, test_turn_id, test_eva,
				test_acc,test_gil);
			Assert::AreEqual(test_string, enemy.name);
			Assert::AreEqual(test_hit_perc, enemy.hit_perc);
			Assert::AreEqual(test_attack, enemy.attack);
			Assert::AreEqual(test_defense, enemy.defense);
			Assert::AreEqual(test_mag_defense, enemy.mag_defense);
			Assert::AreEqual(test_eva_perc, enemy.eva_perc);
			Assert::AreEqual(test_exp, enemy.exp);
			Assert::AreEqual(test_turn_id, enemy.turn_ID);
			Assert::AreEqual(test_eva, enemy.eva);
			Assert::AreEqual(test_acc, enemy.acc);
			Assert::AreEqual(test_gil, enemy.gil);
		}
	
	};
}

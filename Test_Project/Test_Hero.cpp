#include "pch.h"
#include "CppUnitTest.h"
#include "../201_Honors/Hero.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestHero
{
	TEST_CLASS(TestHero)
	{
	public:
		
		TEST_METHOD(Test_Hero_Init) {
			std::string test_string = "Test Fighter";
			unsigned int test_hit_perc = 10, testHP = 35, test_attack = 6, test_defense = 4, test_mag_defense = 8,
				test_eva_perc = 3, test_exp = 6, test_turn_id = 0, test_str=20, test_agi=5,
				test_inte=1, test_vit=10, test_luck=5, test_eva=5;
			Hero hero(test_string, test_hit_perc, testHP, test_attack, test_defense,
				test_mag_defense, test_eva_perc, test_exp, test_turn_id, test_str, test_agi,
				test_inte, test_vit, test_luck, test_eva, Hero::fighter);

			Assert::AreEqual(test_string, hero.name);
			Assert::AreEqual(test_hit_perc, hero.hit_perc);
			// Attack is set by Attack_Formula, which is a private method
			// For the above stats it should equal 10
			test_attack = 10;
			Assert::AreEqual(test_attack, hero.attack);
			Assert::AreEqual(test_defense, hero.defense);
			Assert::AreEqual(test_mag_defense, hero.mag_defense);
			Assert::AreEqual(test_eva_perc, hero.eva_perc);
			Assert::AreEqual(test_exp, hero.exp);
			Assert::AreEqual(test_turn_id, hero.turn_ID);
			Assert::AreEqual(test_str, hero.Get_Str());
			Assert::AreEqual(test_agi, hero.Get_Agi());
			Assert::AreEqual(test_inte, hero.Get_Inte());
			Assert::AreEqual(test_vit, hero.Get_Vit());
			Assert::AreEqual(test_luck, hero.Get_Luck());
			Assert::AreEqual(test_eva, hero.Get_Eva());
		}

		TEST_METHOD(Test_Hero_Attack_Target) {
			std::string test_string = "Test Fighter";
			int test_hit_perc = 10;
			unsigned int test_HP = 35, test_attack = 6, test_defense = 4, test_mag_defense = 8,
				test_eva_perc = 3, test_exp = 6, test_turn_id = 0, test_str = 20, test_agi = 5,
				test_inte = 1, test_vit = 10, test_luck = 5, test_eva = 5;
			Hero hero(test_string, test_hit_perc, test_HP, test_attack, test_defense,
				test_mag_defense, test_eva_perc, test_exp, test_turn_id, test_str, test_agi,
				test_inte, test_vit, test_luck, test_eva, Hero::fighter);

			test_string = "Dummy";
			test_HP = 100;
			test_hit_perc = 85;
			unsigned int test_acc = 0, test_gil = 6;
			Enemy enemy(test_string, test_hit_perc, test_HP, test_attack, test_defense,
				test_mag_defense, test_eva_perc, test_exp, test_turn_id, test_eva,
				test_acc, test_gil);
			
			// Equip test weapon
			hero.weapon = Weapon(6, 0, 0);
			hero.armor = Armor(0, 0);

			int damage = hero.Attack_Target(enemy);

			Assert::IsTrue(damage >= 1);
			Assert::IsTrue(damage <= 16);
			Assert::IsTrue(enemy.hp <= 99);
		}

	};
}

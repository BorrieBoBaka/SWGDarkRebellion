#ifndef BORDICE_H_
#define BORDICE_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/borrie/BorrieRPG.h"

//#include "templates/roleplay/RoleplayManager.h"

class BorDice : public Logger {
public:
	static bool GetCommandIsDie(String command) {
		if (GetDiceNum(command) == 0)
			return false;
		else if (GetDiceValue(command) == 0)
			return false;
		else
			return true;
	}

	static int GetDiceNum(String roll) {
		String sNumDice;
		StringTokenizer args(roll);
		args.setDelimeter("d");
		if (!args.hasMoreTokens())
			return 0;
		else {
			args.getStringToken(sNumDice);
			return Integer::valueOf(sNumDice);
		}
	}

	static int GetDiceValue(String roll) {
		String sDiceValue;
		StringTokenizer args(roll);
		args.setDelimeter("d");
		if (!args.hasMoreTokens())
			return 0;
		else {
			if (args.hasMoreTokens()) {
				args.getStringToken(sDiceValue);
				return Integer::valueOf(sDiceValue);
			} else
				return 0;
		}
	}

	static String RollRPDie(CreatureObject* creature, String roll, int mod = 0) {
		int numDice, diceValue, nTempResult, nResult = 0;
		String sNumDice, sDiceValue, DiceRollString;
		StringTokenizer args(roll);
		args.setDelimeter("d");
		if (!args.hasMoreTokens()) {
			// Return. Send message that there was no proper set up.
			return "fail";
		} else {
			args.getStringToken(sNumDice);
			if (args.hasMoreTokens()) {
				args.getStringToken(sDiceValue);
				numDice = Integer::valueOf(sNumDice);
				diceValue = Integer::valueOf(sDiceValue);
				if (numDice > 10 || numDice < 1) {
					creature->sendSystemMessage("You cannot roll more than 1 - 10 dice.");
					return "fail";
				} else if (diceValue > 100 || diceValue < 2) {
					creature->sendSystemMessage("Accepted die are d2 - 100");
					return "fail";
				}
				for (int i = 0; i < numDice; i++) {
					nTempResult = System::random(diceValue - 1) + 1;
					DiceRollString += String::valueOf(nTempResult);
					nResult += nTempResult;
					if (i == numDice - 1)
						DiceRollString += " =";
					else
						DiceRollString += " + ";
				}

				if (mod != 0)
					return "Roll " + sNumDice + "d" + sDiceValue + ": " + DiceRollString + " (Modifier: " + String::valueOf(mod) +
						   ") Result: " + String::valueOf(nResult + mod);
				else
					return "Roll " + sNumDice + "d" + sDiceValue + ": " + DiceRollString + " Result: " + String::valueOf(nResult);

			} else {
				// Return, we need the full thing.
				return "fail";
			}
		}

		return "fail";
	}

	static String RollSkill(CreatureObject* creature, String skillName) {
		int value = creature->getSkillMod("rp_" + skillName);
		int Roll = System::random(19) + 1;
		return BorrieRPG::Capitalize(skillName) + " check : 1d20 = " + String::valueOf(Roll) + " + Modifier: " + String::valueOf(value) +
			   ". Result: " + String::valueOf(value + Roll);
	}

	static int Roll(int dieCount, int dieType) {
		int total = 0;
		for(int i = 0;i<dieCount;i++) {
			int roll = System::random(dieType - 1) + 1;
			total += roll;
		}
		return total;
	}



	/*
	static String RollStat(CreatureObject* creature, String statName) {
		RPStatData* statData = RoleplayManager::instance()->getStatDataByEither(statName);
		String statValue = creature->getLocalData(statData->getName());
		if (statValue == "XXERRORXX")
			return "fail";
		int statNum = Integer::valueOf(statValue);
		if (statData->isAffectedByArmor()) {
			statNum - SovCharacter::GetArmorStatModifier(creature);
		}
		int Roll = System::random(19) + 1;
		return Sovereignty::Capitalize(statName) + " check: 1d20 = " + String::valueOf(Roll) + " + Modifier: " + String::valueOf(statNum) +
			   ". Result: " + String::valueOf(Roll + statNum);
	} */

};

#endif /*BORDICE_H_*/
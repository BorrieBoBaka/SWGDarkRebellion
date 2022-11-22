#ifndef BORCHARACTER_H_
#define BORCHARACTER_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"

//#include "templates/roleplay/RoleplayManager.h"

#include "server/zone/borrie/BorrieRPG.h"
#include "server/zone/borrie/BorSkill.h"
#include "server/zone/borrie/BorDice.h"

#include "server/db/ServerDatabase.h"

#include "server/zone/objects/creature/sui/ForceSensitivePromptSuiCallback.h"

#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"

#include "templates/params/creature/CreatureAttribute.h"


class BorCharacter : public Logger {
public:
	static bool GetStringIsPool(String pool) {
		if (pool == "health")
			return true;
		else if (pool == "action")
			return true;
		else if (pool == "force")
			return true;
		else if (pool == "will")
			return true;
		else
			return false;
	}

	static ManagedReference<ArmorObject*> GetArmorAtSlot(CreatureObject* creature, String slot) {
		return creature->getWearablesDeltaVector()->getArmorAtSlot(slot);
	}

	static void ToggleJedi(CreatureObject* dm, CreatureObject* creature) {
		Locker clocker(dm, creature);

		ManagedReference<PlayerObject*> targetGhost = creature->getPlayerObject();
		if(targetGhost == nullptr)
			return;

		int jediState = targetGhost->getJediState();

		if(jediState > 1)
			jediState = 0;
		else if(jediState == 0) 
			jediState = 2;

		targetGhost->setJediState(jediState);

		if(jediState == 2)
			dm->sendSystemMessage("You've enabled " + creature->getFirstName() + " to be Force Sensitive");
		else 
			dm->sendSystemMessage("You've disabled " + creature->getFirstName() + " from being Force Sensitive");
	}

	static void PromptForceQuestion(CreatureObject* creature) {
		int hasDecided = creature->getStoredInt("fs_chosen");

		if(hasDecided != 1) {
			//Prompt them
			ManagedReference<SuiListBox*> box = new SuiListBox(creature, SuiWindowType::JUKEBOX_SELECTION);
			box->setCancelButton(true, "Decide Later");
			box->setCallback(new ForceSensitivePromptSuiCallback(creature->getZoneServer()));
			box->setPromptTitle("Force Sensitivity");
			String message = "You must choose whether or not this character is sensitive to the Force. ";
			message += "If you choose to be Force Sensitive, you will have the option to train your ability in the Force, becoming Jedi, Sith, or something else. ";
			message += "If you opt not to be Force Sensitive, you will have an extra 20 skill points available to you, as well as 5 more free skills you can train. ";
			message += "WARNING: Once you've made this decision, it is final. So choose carefully.";
			box->setPromptText(message);
			box->setOkButton(false, "@");
			box->addMenuItem("I am Force Sensitive (-20 Skill Points)");
			box->addMenuItem("I am NOT Force Sensitive (+5 Free Skills)");
			creature->getPlayerObject()->addSuiBox(box);
			creature->sendMessage(box->generateMessage());
		}
	}

	static void AddState(CreatureObject* creature, String state, bool alertEveryone = false) {
		Locker clocker(creature);
		if (state == "stunned" || state == "stun") {
			creature->setState(CreatureState::STUNNED);
			if (alertEveryone)
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has been stunned!");
		} else if (state == "blinded" || state == "blind") {
			creature->setState(CreatureState::BLINDED);
			if (alertEveryone)
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has been blinded!");
		} else if (state == "immobilized" || state == "immobile") {
			creature->setState(CreatureState::IMMOBILIZED);
			if (alertEveryone)
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has been immobilized!");
		} else if (state == "knockeddown" || state == "knockdown" || state == "kd") {
			if (alertEveryone)
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has been knocked down!");
		} else if (state == "burning" || state == "onfire" || state == "fire" || state == "burn") {
			creature->setState(CreatureState::ONFIRE);
			if (alertEveryone)
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has set on fire!");
		} else if (state == "bleeding" || state == "bleed" || state == "bleeding") {
			creature->setState(CreatureState::BLEEDING);
			if (alertEveryone)
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has started bleeding!");
		} else {
			creature->sendSystemMessage("ERROR: Invalid state specified. Try stun, blind, immobile, knockdown, fire, or bleed.");
		}
	}

	static void RemoveAllStates(CreatureObject* creature, bool allStates) {
		Locker clocker(creature);
		creature->clearState(CreatureState::STUNNED);
		creature->clearState(CreatureState::BLINDED);
		creature->clearState(CreatureState::IMMOBILIZED);
		if(allStates) {
			creature->clearState(CreatureState::ONFIRE);
			creature->clearState(CreatureState::BLEEDING);
		}
	}

	static void ApplyEndTurnStateDamages(CreatureObject* creature) {
		StringBuffer text;
		int damageToTake = 0;
		if(creature->hasState(CreatureState::ONFIRE)) {
			int roll = (System::random(4) + 1) + (System::random(4) + 1);
			text << " has taken " << roll << " damage for being on fire!";
			damageToTake += roll;
		}

		if(creature->hasState(CreatureState::BLEEDING)) {
			int roll = (System::random(4) + 1);
			text << " has taken " << roll << " damage from bleeding!";
			damageToTake += roll;
		}

		if(damageToTake != 0) {
			ModPool(creature, "health", damageToTake * -1);
			creature->sendSystemMessage(text.toString());
		}
	}

	static void RemoveState(CreatureObject* creature, String state, bool alertEveryone = false) {
		Locker clocker(creature);
		if (state == "stunned" || state == "stun") {
			creature->clearState(CreatureState::STUNNED);
			if (alertEveryone)
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " is no longer stunned.");
		} else if (state == "blinded" || state == "blind") {
			creature->clearState(CreatureState::BLINDED);
			if (alertEveryone)
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " is no longer blind.");
		} else if (state == "immobilized" || state == "immobile") {
			creature->clearState(CreatureState::IMMOBILIZED);
			if (alertEveryone)
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " is no longer immobilized.");
		} else if (state == "burning" || state == "onfire" || state == "fire" || state == "burn") {
			creature->clearState(CreatureState::ONFIRE);
			if (alertEveryone)
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " is no longer on fire.");
		} else if (state == "bleeding" || state == "bleed" || state == "bleeding") {
			creature->clearState(CreatureState::BLEEDING);
			if (alertEveryone)
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " is no longer bleeding.");
		} else {
			creature->sendSystemMessage("ERROR: Invalid state specified. Try stun, blind, immobile, knockdown, fire, or bleed.");
		}
	}

	static void ClearStates(CreatureObject* creature, bool alertEveryone = false) {
		Locker clocker(creature);
		creature->clearState(CreatureState::STUNNED);
		creature->clearState(CreatureState::BLINDED);
		creature->clearState(CreatureState::IMMOBILIZED);
		creature->clearState(CreatureState::ONFIRE);
		creature->clearState(CreatureState::BLEEDING);
		if (alertEveryone)
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has been cleared of all states.");
	}

	static void ModPool(CreatureObject* creature, String pool, int mod, bool suppressMessage = false) {
		Locker clocker(creature);
		int max = 0;
		int current = 0;
		int finalPool = 0;
		int poolID = GetHAMFromPool(pool);
		if (poolID == -1) {
			creature->sendSystemMessage("ERROR: You've not specified an actual pool. Valid pools are: health, action, will, and force.");
			return;
		}
		if (poolID > 8) { //If above 8, its a force pool.
			if (creature->isPlayerCreature()) {
				max = creature->getPlayerObject()->getForcePowerMax();
				current = creature->getPlayerObject()->getForcePower();
				if (current + mod > max)
					finalPool = 0;
				else if (current + mod > max)
					finalPool = max;
				else
					finalPool = current + mod;

				if(finalPool < 0) finalPool = 0;

				creature->getPlayerObject()->setForcePower(finalPool, true);
				if(!suppressMessage)
					BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + "'s " + pool + " pool has changed by " + String::valueOf(mod) + "! (Was: " + String::valueOf(current) + ")");
			} 
		} else {
			max = creature->getMaxHAM(poolID);
			current = creature->getHAM(poolID);
			if (current + mod > max)
				finalPool = 0;
			else if (current + mod > max)
				finalPool = max;
			else
				finalPool = current + mod;

			if(finalPool < 0) finalPool = 0;

			creature->setHAM(poolID, finalPool, true);	
			if(!suppressMessage)
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + "'s " + pool + " pool has changed by " + String::valueOf(mod) + "! (Was: " + String::valueOf(current) + ")");
			if (poolID == 0 && finalPool == 0) {
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has run out of health!");
			}
			if (poolID == 6 && finalPool == 0) {
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has run out of will!");
			}
		}			
	}

	static void FillPool(CreatureObject* creature, String pool, bool suppressMessage = false) {
		Locker clocker(creature);
		int max = 0;
		int current = 0;
		int poolID = GetHAMFromPool(pool);
		if (poolID != -1) {
			if (poolID > 8) { //Force Power
				if(creature->getPlayerObject() != nullptr) {
					max = creature->getPlayerObject()->getForcePowerMax();
					current = creature->getPlayerObject()->getForcePower();
					creature->getPlayerObject()->setForcePower(max, true);
					if (!suppressMessage)
						BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + "'s " + pool + " pool has been filled! (Was: " + String::valueOf(current) + ")");
				}
				
			} else {
				max = creature->getMaxHAM(poolID);
				current = creature->getHAM(poolID);
				creature->setHAM(poolID, max, true);	
				if (!suppressMessage)
					BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + "'s " + pool + " pool has been filled! (Was: " + String::valueOf(current) + ")");
			}
		} else {
			creature->sendSystemMessage("ERROR: You've not specified an actual pool. Valid pools are: health, action, will, and force.");
		}
	}

	static void FillAllPools(CreatureObject* creature,  bool suppressMessage = false) {
		Locker clocker(creature);
		int lastHealth = creature->getHAM(0);
		int lastAction = creature->getHAM(3);
		int lastWill = creature->getHAM(6);
		int lastForce = 0;
		if (creature->isPlayerCreature()) {
			lastForce = creature->getPlayerObject()->getForcePower(); 
		}

		FillPool(creature, "health", true);
		FillPool(creature, "action", true);
		FillPool(creature, "will", true);
		FillPool(creature, "force", true);

		String report = creature->getFirstName() + " has fully rested, filling all of their pools.";
		report += " (Was H:" + String::valueOf(lastHealth);
		report += ", A:" + String::valueOf(lastAction);
		report += ", W:" + String::valueOf(lastWill);

		if (creature->isPlayerCreature()) {
			if (creature->getPlayerObject()->getForcePowerMax() > 0) {
				report += ", F:" + String::valueOf(lastForce) + ")";
			} else {
				report += ")";
			}
		} else {
			report += ")";
		}		

		if (!suppressMessage)
			BorrieRPG::BroadcastMessage(creature, report);
	}

	static void PerformShortRest(CreatureObject* creature) {
		Locker clocker(creature);
		int lastHealth = creature->getHAM(0);
		int lastAction = creature->getHAM(3);
		int lastWill = creature->getHAM(6);
		if(lastWill < 2) {
			creature->sendSystemMessage("You don't have enough will points to perform a short rest.");
			return;
		}

		int lastForce = 0;
		if (creature->isPlayerCreature()) {
			lastForce = creature->getPlayerObject()->getForcePower(); 
		}

		ModPool(creature, "health", creature->getSkillMod("rp_health") / 2);
		FillPool(creature, "action", true);
		FillPool(creature, "force", true);
		ModPool(creature, "will", -2);
	}

	static int GetHAMFromPool(String pool) {
		if (pool == "health" || pool == "hp")
			return 0;
		else if (pool == "action" || pool == "ap")
			return 3;
		else if (pool == "will" || pool == "wp")
			return 6;
		else if (pool == "force" || pool == "fp")
			return 999;
		else
			return -1;
	}

	static bool HealWithStimpack(StimPack* stim, CreatureObject* creature, CreatureObject* targetCreature) {
		int medicineDC = stim->getDieCheck();
		int medicSkill = creature->getSkillMod("rp_medicine");
		int roll = BorDice::Roll(1, 20);

		if(roll == 20 || roll + medicSkill >= medicineDC) {
			int dieCount = stim->getDieCount();
			int dieType = stim->getDieType();
			int healRoll = BorDice::Roll(dieCount, dieType);
			ModPool(targetCreature, "health", healRoll, true);
			if(targetCreature->getHAM(CreatureAttribute::ACTION) < 1)
				ModPool(targetCreature, "will", -1, true);
			else 
				ModPool(targetCreature, "action", -1, true);
			BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " successfully heals " + targetCreature->getFirstName() + " for " + String::valueOf(healRoll) + " damage! (1d20 Result: " + String::valueOf(roll) + " + " + String::valueOf(medicSkill) + " = " +  String::valueOf(roll + medicSkill) + " vs. DC:" + String::valueOf(medicineDC) + ")"); 
			return true;
		} else {
			if(targetCreature->getHAM(CreatureAttribute::ACTION) < 1)
				ModPool(targetCreature, "will", -1, true);
			else 
				ModPool(targetCreature, "action", -1, true);
			BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " fails to heal " + targetCreature->getFirstName() + " (1d20 Result: " + String::valueOf(roll) + " + " + String::valueOf(medicSkill) + " = " +  String::valueOf(roll + medicSkill) + " vs. DC:" + String::valueOf(medicineDC) + ")");
			return false;
		}
	}

	static bool PerformImprovHeal(CreatureObject* creature, CreatureObject* targetCreature) {
		int medicineDC = 10;
		int medicSkill = creature->getSkillMod("rp_medicine");
		int roll = BorDice::Roll(1, 20);
		if(roll == 20 || roll + medicSkill >= medicineDC) {
			int dieCount = 1;
			int dieType = 2 + medicSkill;
			int healRoll = BorDice::Roll(dieCount, dieType);
			ModPool(targetCreature, "health", healRoll, true);
			if(targetCreature->getHAM(CreatureAttribute::ACTION) < 1)
				ModPool(targetCreature, "will", -1, true);
			else 
				ModPool(targetCreature, "action", -1, true);

			BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " successfully improvise heals " + targetCreature->getFirstName() + " for " + String::valueOf(healRoll) + " damage! (1d20 Result: " + String::valueOf(roll) + " + " + String::valueOf(medicSkill) + " = " +  String::valueOf(roll + medicSkill) + " vs. DC:" + String::valueOf(medicineDC) + ")");
			return true;
		} else {
			if(targetCreature->getHAM(CreatureAttribute::ACTION) < 1)
				ModPool(targetCreature, "will", -1, true);
			else 
				ModPool(targetCreature, "action", -1, true);

			BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " fails to improvise heal " + targetCreature->getFirstName() + " (1d20 Result: " + String::valueOf(roll) + " + " + String::valueOf(medicSkill) + " = " +  String::valueOf(roll + medicSkill) + " vs. DC:" + String::valueOf(medicineDC) + ")");
			return false;
		}
	}

	static void InspectPlayer(CreatureObject* dm, CreatureObject* target) {
		ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(dm, SuiWindowType::NONE);
		suiBox->setPromptTitle(target->getDisplayedName()); 
		StringBuffer infoText;

		String factionTag = target->getStoredString("faction_current");

		infoText << "\\#FF7000[INFO]\\#." << endl;
		infoText << "Level: " << GetPlayerLevel(target) << endl;
		infoText << "Force Sensitivity Level: " << GetForceImmersionLevel(target) << endl;

		if(factionTag != "") {
			infoText << "\\#FF7000[FACTION]\\#." << endl;
			infoText << "Faction: " << target->getStoredString("faction_current") << endl;
			infoText << "Rank: " << target->getStoredInt("rank_" + factionTag) << endl;
		}
		
		infoText << "\\#FF7000[CURRENCY]\\#." << endl;
		infoText << "Cash: " << target->getCashCredits() << endl;
		infoText << "Bank: " << target->getBankCredits() << endl;
		infoText << "\\#FF7000[ATTRIBUTES]\\#." << endl;
		infoText << "Awareness: " << target->getSkillMod("rp_awareness") << endl; 
		infoText << "Charisma: " << target->getSkillMod("rp_charisma") << endl; 
		infoText << "Constitution: " << target->getSkillMod("rp_constitution") << endl; 
		infoText << "Dexterity: " << target->getSkillMod("rp_dexterity") << endl; 
		infoText << "Intelligence: " << target->getSkillMod("rp_intelligence") << endl; 
		infoText << "Mindfulness: " << target->getSkillMod("rp_mindfulness") << endl; 
		infoText << "Precision: " << target->getSkillMod("rp_precision") << endl; 
		infoText << "Strength: " << target->getSkillMod("rp_strength") << endl; 
		infoText << "\\#FF7000[SKILLS]\\#." << endl;
		infoText << "Armor: " << target->getSkillMod("rp_armor") << endl; 
		infoText << "Athletics: " << target->getSkillMod("rp_athletics") << endl; 
		infoText << "Bluff: " << target->getSkillMod("rp_bluff") << endl; 
		infoText << "Composure: " << target->getSkillMod("rp_composure") << endl; 
		infoText << "Computers: " << target->getSkillMod("rp_computers") << endl; 
		infoText << "Defending: " << target->getSkillMod("rp_defending") << endl; 
		infoText << "Demolitions: " << target->getSkillMod("rp_demolitions") << endl; 
		infoText << "Engineering: " << target->getSkillMod("rp_engineering") << endl; 
		infoText << "Intimidation: " << target->getSkillMod("rp_intimidation") << endl; 
		infoText << "Investigation: " << target->getSkillMod("rp_investigation") << endl; 
		infoText << "Larceny: " << target->getSkillMod("rp_larceny") << endl; 
		infoText << "Maneuverability: " << target->getSkillMod("rp_maneuverability") << endl; 
		infoText << "Mechanics: " << target->getSkillMod("rp_mechanics") << endl; 
		infoText << "Medicine: " << target->getSkillMod("rp_medicine") << endl; 
		infoText << "Melee: " << target->getSkillMod("rp_melee") << endl; 
		infoText << "Persuasion: " << target->getSkillMod("rp_persuasion") << endl; 
		infoText << "Piloting: " << target->getSkillMod("rp_piloting") << endl; 
		infoText << "Ranged: " << target->getSkillMod("rp_ranged") << endl; 
		infoText << "Resolve: " << target->getSkillMod("rp_resolve") << endl; 
		infoText << "Science: " << target->getSkillMod("rp_science") << endl; 
		infoText << "Slicing: " << target->getSkillMod("rp_slicing") << endl; 
		infoText << "Stealth: " << target->getSkillMod("rp_stealth") << endl; 
		infoText << "Survival: " << target->getSkillMod("rp_survival") << endl; 
		infoText << "Throwing: " << target->getSkillMod("rp_throwing") << endl; 
		infoText << "Unarmed: " << target->getSkillMod("rp_unarmed") << endl; 
		infoText << "\\#FF7000[FREE POINTS]\\#." << endl;
		infoText << "Attributes: " << target->getStoredInt("starter_attr_points") << endl;
		infoText << "Skills: " << target->getStoredInt("starter_skill_points")  << endl;

		suiBox->setPromptText(infoText.toString());

		dm->sendMessage(suiBox->generateMessage());
	}

	static int GetForceImmersionLevel(CreatureObject* creature) {
		if(creature->hasSkill("rp_force_prog_master")) 
			return 6;
		else if(creature->hasSkill("rp_force_prog_rank_04")) 
			return 5;
		else if(creature->hasSkill("rp_force_prog_rank_03")) 
			return 4;
		else if(creature->hasSkill("rp_force_prog_rank_02")) 
			return 3;
		else if(creature->hasSkill("rp_force_prog_rank_01")) 
			return 2;
		else if(creature->hasSkill("rp_force_prog_novice")) 
			return 1;
		else
			return 0;
	}

	static bool GetSkillIsTrainable(String skill) {
		if(skill.contains("admin_"))
			return false;
		else if(skill.contains("rp_force_prog")) 
			return false;
		else if(skill == "rp_training_jedi_rank_08")
			return false;
		else if(skill == "rp_training_jedi_rank_09")
			return false;
		else if(skill == "rp_training_jedi_rank_10")
			return false;
		else if(skill == "rp_training_jedi_rank_master")
			return false;
		else if(skill == "rp_training_sith_rank_08")
			return false;
		else if(skill == "rp_training_sith_rank_09")
			return false;
		else if(skill == "rp_training_sith_rank_10")
			return false;
		else if(skill == "rp_training_sith_rank_master")
			return false;
		else
			return true;		
	}

	static int GetPlayerLevel(CreatureObject* creature) {
		int level = 1;

		level += GetSkillLevelValue(creature, "melee");
		level += GetSkillLevelValue(creature, "intimidation");
		level += GetSkillLevelValue(creature, "unarmed");
		level += GetSkillLevelValue(creature, "lightsaber");
		level += GetSkillLevelValue(creature, "ranged");
		level += GetSkillLevelValue(creature, "mechanics");
		level += GetSkillLevelValue(creature, "demolitions");
		level += GetSkillLevelValue(creature, "engineering");
		level += GetSkillLevelValue(creature, "larceny");
		level += GetSkillLevelValue(creature, "stealth");
		level += GetSkillLevelValue(creature, "maneuverability");
		level += GetSkillLevelValue(creature, "throwing");
		level += GetSkillLevelValue(creature, "investigation");
		level += GetSkillLevelValue(creature, "piloting");
		level += GetSkillLevelValue(creature, "survival");
		level += GetSkillLevelValue(creature, "sense");
		level += GetSkillLevelValue(creature, "slicing");
		level += GetSkillLevelValue(creature, "computers");
		level += GetSkillLevelValue(creature, "medicine");
		level += GetSkillLevelValue(creature, "science");
		level += GetSkillLevelValue(creature, "persuasion");
		level += GetSkillLevelValue(creature, "bluff");
		level += GetSkillLevelValue(creature, "composure");
		level += GetSkillLevelValue(creature, "resolve");
		level += GetSkillLevelValue(creature, "athletics");
		level += GetSkillLevelValue(creature, "lightning");
		level += GetSkillLevelValue(creature, "armor");
		level += GetSkillLevelValue(creature, "defending");
		level += GetSkillLevelValue(creature, "telekinesis");
		level += GetSkillLevelValue(creature, "control");
		level += GetSkillLevelValue(creature, "alter");
		level += GetSkillLevelValue(creature, "inward");

		return level;
	}

	static int GetSkillLevelValue(CreatureObject* creature, String skill) {
		int level = 0;
		int skillMod = creature->getSkillMod("rp_" + skill);
		if (skillMod >= 5 && skillMod < 10)
			level += 1;
		else if (skillMod == 10)
			level += 2;
		return level;
	}

	static void RewardGeneralRPExperience(CreatureObject* creature, CreatureObject* dm, int amount) {
		creature->getZoneServer()->getPlayerManager()->awardExperience(creature, "rp_general", amount, true);
		dm->sendSystemMessage("Rewarded " + creature->getFirstName() + " " + String::valueOf(amount) + " roleplay experience.");
	}

	static void ModifyDailyFactionContribution(CreatureObject* creature, CreatureObject* dm, int amount) {
		if(creature->isPlayerCreature()) {

			PlayerObject* targetPlayer = creature->getPlayerObject();
			if(targetPlayer == nullptr) {
				dm->sendSystemMessage("Target is not a player creature.");
			}

			if(amount == 0) {
				dm->sendSystemMessage("You need to input a negative or positive value to change the target's faction contribution.");
				return;
			}
		
			if(creature->getStoredString("faction_current") != "") {
				int currentFood = targetPlayer->getFoodFilling();
				int maxFood = targetPlayer->getFoodFillingMax();
				int foodAddScore = currentFood + amount;
				//Prevent overflow
				if(foodAddScore > maxFood) {
					foodAddScore = maxFood;
				}
				targetPlayer->setFoodFilling(foodAddScore, true);
				if(amount > 0) {
					creature->sendSystemMessage("You've gained " + String::valueOf(amount) + " points toward your daily faction contribution.");
					dm->sendSystemMessage("You've given " + String::valueOf(amount) + " daily faction contribution points to " + creature->getFirstName());
				} else {
					creature->sendSystemMessage("You've lost " + String::valueOf(amount) + " points toward your daily faction contribution.");
					dm->sendSystemMessage("You've removed " + String::valueOf(amount) + " daily faction contribution points from " + creature->getFirstName());
				}			
			} else {
				dm->sendSystemMessage("Target is not in a faction.");
			}
		} else {
			dm->sendSystemMessage("Target is not a player creature.");
		}
	}

	static void ModifyOverallFactionLoyalty(CreatureObject* creature, CreatureObject* dm, int amount) {
		if(creature->isPlayerCreature()) {

			PlayerObject* targetPlayer = creature->getPlayerObject();
			if(targetPlayer == nullptr) {
				dm->sendSystemMessage("Target is not a player creature.");
			}

			if(amount == 0) {
				dm->sendSystemMessage("You need to input a negative or positive value to change the target's faction loyalty.");
				return;
			}
		
			if(creature->getStoredString("faction_current") != "") {
				int currentDrink = targetPlayer->getDrinkFilling();
				int maxDrink = targetPlayer->getDrinkFillingMax();
				int drinkAddScore = currentDrink + amount;
				//Prevent overflow
				if(drinkAddScore > maxDrink) {
					drinkAddScore = maxDrink;
				}
				targetPlayer->setDrinkFilling(drinkAddScore, true);
				if(amount > 0) {
					creature->sendSystemMessage("You've gained " + String::valueOf(amount) + " points toward your overall faction loyalty.");
					dm->sendSystemMessage("You've given " + String::valueOf(amount) + " overall faction loyalty points to " + creature->getFirstName());
				} else {
					creature->sendSystemMessage("You've lost " + String::valueOf(amount) + " points toward your overall faction loyalty.");
					dm->sendSystemMessage("You've removed " + String::valueOf(amount) + " overall faction loyalty points from " + creature->getFirstName());
				}				
			} else {
				dm->sendSystemMessage("Target is not in a faction.");
			}
		} else {
			dm->sendSystemMessage("Target is not a player creature.");
		}
	}

	static void ResetFactionReportCooldown(CreatureObject* creature, CreatureObject* dm) {
		if(creature->isPlayerCreature()) {
			PlayerObject* targetPlayer = creature->getPlayerObject();
			if(targetPlayer == nullptr) {
				dm->sendSystemMessage("Target is not a player creature.");
			}

			if(creature->getStoredString("faction_current") == "") {
				dm->sendSystemMessage("Target is not in a faction.");
				return;
			}

			targetPlayer->deleteScreenPlayData("BorFactionManager", "ReportDelay");
			dm->sendSystemMessage("The target is now able to report in to their faction.");
		} else {
			dm->sendSystemMessage("Target is not a player creature.");
		}
	}

	static void RewardXPForLastRoll(CreatureObject* creature, CreatureObject* dm) {
		int roll = creature->getLastSkillRoll();
		String skill = creature->getLastRolledSkill();
		String skillParent = BorSkill::GetSkillParent(skill);
		if (skillParent != "") { //Skill was rolled.
			//Reward Parent 10%
			int parentReward = roll / 10;
			creature->getZoneServer()->getPlayerManager()->awardExperience(creature, skill, roll, true); 
			creature->getZoneServer()->getPlayerManager()->awardExperience(creature, skillParent, parentReward, true); 
			dm->sendSystemMessage("Rewarded " + creature->getFirstName() + " " + String::valueOf(roll) + " @skl_n:" + skill + " experience.");
		} else { //Attribute was rolled.
			int reward = roll / 10;
			creature->getZoneServer()->getPlayerManager()->awardExperience(creature, skill, reward, true); 
			dm->sendSystemMessage("Rewarded " + creature->getFirstName() + " " + String::valueOf(reward) + " @skl_n:" + skill + " experience.");
		}
	}

	static void RewardXPForRoll(CreatureObject* creature, CreatureObject* dm, String skill, int roll) {
		String skillParent = BorSkill::GetSkillParent(skill);
		if (skillParent != "") { // Skill was rolled.
			// Reward Parent 10%
			int parentReward = roll / 10;
			creature->getZoneServer()->getPlayerManager()->awardExperience(creature, "rp_" + skill, roll, true);
			creature->getZoneServer()->getPlayerManager()->awardExperience(creature, "rp_" + skillParent, parentReward, true);
			dm->sendSystemMessage("Rewarded " + creature->getFirstName() + " " + String::valueOf(roll) + " @skl_n:rp_" + skill + " experience.");
		} else { // Attribute was rolled.
			int reward = roll / 10;
			creature->getZoneServer()->getPlayerManager()->awardExperience(creature, "rp_" + skill, reward, true);
			dm->sendSystemMessage("Rewarded " + creature->getFirstName() + " " + String::valueOf(reward) + " @skl_n:rp_" + skill + " experience.");
		}
	}

	static void RewardCreditsByLevel(CreatureObject* creature, CreatureObject* dm, int multiplier = 100) {
		int playerLevel = GetPlayerLevel(creature);
		int credits = playerLevel * multiplier;
		if(credits < 1) return;
		creature->addCashCredits(credits);
		creature->sendSystemMessage("You've been awarded " + String::valueOf(credits) + " credits!");
		dm->sendSystemMessage("You've rewarded " + creature->getFirstName() + " " + String::valueOf(credits) + " credits.");
	}

	static void ModifyFreePoints(CreatureObject* creature, CreatureObject* target, String type, int amount) { 
		int currentPoints = target->getStoredInt("starter_" + type + "_points");
		target->setStoredInt("starter_" + type + "_points", currentPoints + amount);
		if(type == "attr") {
			if(amount > 0) {
				creature->sendSystemMessage("You've granted " + target->getFirstName() + " " + String::valueOf(amount) + " free attribute points.");
				target->sendSystemMessage("You've been granted " + String::valueOf(amount) + " free attribute points! Apply them using the '/train' command.");
			} else {
				creature->sendSystemMessage("You've removed from " + target->getFirstName() + " " + String::valueOf(amount) + " free attribute points.");
				target->sendSystemMessage(String::valueOf(amount) + " free attribute points have been removed.");
			}			
		} else if(type == "skill") {
			if(amount > 0) {
				creature->sendSystemMessage("You've granted " + target->getFirstName() + " " + String::valueOf(amount) + " free skill points.");
				target->sendSystemMessage("You've been granted " + String::valueOf(amount) + " free skill points! Apply them using the '/train' command.");
			} else {
				creature->sendSystemMessage("You've removed from " + target->getFirstName() + " " + String::valueOf(amount) + " free skill points.");
				target->sendSystemMessage(String::valueOf(amount) + " free skill points have been removed.");
			}			
		}
	}

	static int GetTargetDistance(CreatureObject* creature, SceneObject* object) {
		if (object == nullptr)
			return -1;
		return (int)(creature->getDistanceTo(object));
	}

	static void LowerPosture(CreatureObject* creature) {
		if(creature->isStanding()) {
			//Kneel
			creature->setPosture(CreaturePosture::CROUCHED, true, true);
		} else if(creature->isKneeling()) {
			//Prone
			creature->setPosture(CreaturePosture::PRONE, true, true);
		}
	}
	
	static int GetDistance(CreatureObject* creature, float x, float z, float y) {
		Coordinate coord;
		coord.setPositionX(x);
		coord.setPositionZ(z);
		coord.setPositionY(y);
		return (int)(creature->getDistanceTo(&coord));
	}
	

	static void InitializeRoleplayMove(CreatureObject* creature) {
		//Roll Athletics to get bonus movement. Base movement is 10 meters. 
		//int roll = System::random(9) + 1;
		int athletics = creature->getSkillMod("rp_athletics");
		int maneuverability = creature->getSkillMod("rp_maneuverability");

		PlayerObject* ghost = creature->getPlayerObject();
		if (ghost == nullptr)
			return;

		ManagedReference<WaypointObject*> newwaypoint = nullptr;

		// Get previous movement waypoint
		ManagedReference<WaypointObject*> waypoint = ghost->getSurveyWaypoint();

		// Create new waypoint
		if (waypoint == nullptr)
			newwaypoint = (creature->getZoneServer()->createObject(0xc456e788, 1)).castTo<WaypointObject*>();
		else {
			ghost->removeWaypoint(waypoint->getObjectID(), true, false);
			newwaypoint = waypoint.get();
		}

		if(newwaypoint != nullptr) {
			Locker locker(newwaypoint);

			newwaypoint->setCustomObjectName(UnicodeString("Last Position"), false);
			newwaypoint->setPlanetCRC(creature->getZone()->getZoneCRC());
			newwaypoint->setPosition(creature->getPositionX(), creature->getPositionZ(), creature->getPositionY());
			newwaypoint->setColor(WaypointObject::COLOR_PURPLE);
			newwaypoint->setSpecialTypeID(WaypointObject::SPECIALTYPE_RESOURCE);
			newwaypoint->setActive(true);

			ghost->addWaypoint(newwaypoint, false, true); 
		}

		//BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has begun to move. Their range is " + String::valueOf(roll + athletics) +
		//							"m. (Roll: 1d10 = " + String::valueOf(roll) + ")");

		BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has begun to move. Their range is " + String::valueOf(maneuverability + athletics + 6) + "m. ");
									
		creature->sendSystemMessage("Move to your desired destination, using the Last Position waypoint to keep track of your distance. Use the move (rpmove) ability to confirm your movement.");
	}

	static void ConfirmRoleplayMove(CreatureObject* creature) {
		PlayerObject* ghost = creature->getPlayerObject();
		if (ghost == nullptr)
			return;

		// Get previous movement waypoint
		ManagedReference<WaypointObject*> waypoint = ghost->getSurveyWaypoint();
		if(waypoint == nullptr) {
			BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has moved.");
		} else {
			Locker locker(waypoint);
			int distance = GetDistance(creature, waypoint->getPositionX(), waypoint->getPositionZ(), waypoint->getPositionY());
			BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " moved " + String::valueOf(distance) + " meters from their last position.");
		}
		
	}
};

#endif /*BORCHARACTER_H_*/
#ifndef BORCHARACTER_H_
#define BORCHARACTER_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"

//#include "templates/roleplay/RoleplayManager.h"

#include "server/zone/borrie/BorrieRPG.h"
#include "server/zone/borrie/BorSkill.h"

#include "server/db/ServerDatabase.h"

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

	static void ModPool(CreatureObject* creature, String pool, int mod) {
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

				creature->getPlayerObject()->setForcePower(finalPool, true);
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

			creature->setHAM(poolID, finalPool, true);	
			BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + "'s " + pool + " pool has changed by " + String::valueOf(mod) + "! (Was: " + String::valueOf(current) + ")");
			if (poolID == 0 && finalPool == 0) {
				BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has run out of health!");
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
				max = creature->getPlayerObject()->getForcePowerMax();
				current = creature->getPlayerObject()->getForcePower();
				creature->getPlayerObject()->setForcePower(max, true);
				if (!suppressMessage)
					BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + "'s " + pool + " pool has been filled! (Was: " + String::valueOf(current) + ")");
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

	static int GetHAMFromPool(String pool) {
		if (pool == "health")
			return 0;
		else if (pool == "action")
			return 3;
		else if (pool == "will")
			return 6;
		else if (pool == "force")
			return 999;
		else
			return -1;
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
			creature->getZoneServer()->getPlayerManager()->awardExperience(creature, skill, roll, true);
			creature->getZoneServer()->getPlayerManager()->awardExperience(creature, skillParent, parentReward, true);
			dm->sendSystemMessage("Rewarded " + creature->getFirstName() + " " + String::valueOf(roll) + " @skl_n:" + skill + " experience.");
		} else { // Attribute was rolled.
			int reward = roll / 10;
			creature->getZoneServer()->getPlayerManager()->awardExperience(creature, skill, reward, true);
			dm->sendSystemMessage("Rewarded " + creature->getFirstName() + " " + String::valueOf(reward) + " @skl_n:" + skill + " experience.");
		}
	}

	static int GetTargetDistance(CreatureObject* creature, SceneObject* object) {
		if (object == nullptr)
			return -1;
		return (int)(creature->getDistanceTo(object));
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
		int roll = System::random(9) + 1;
		int Athletics = creature->getSkillMod("rp_athletics");

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

		Locker locker(newwaypoint);

		newwaypoint->setCustomObjectName(UnicodeString("Last Position"), false);
		newwaypoint->setPlanetCRC(creature->getZone()->getZoneCRC());
		newwaypoint->setPosition(creature->getPositionX(), creature->getPositionZ(), creature->getPositionY());
		newwaypoint->setColor(WaypointObject::COLOR_PURPLE);
		newwaypoint->setSpecialTypeID(WaypointObject::SPECIALTYPE_RESOURCE);
		newwaypoint->setActive(true);

		ghost->addWaypoint(newwaypoint, false, true); 



		BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " has begun to move. Their range is " + String::valueOf(roll + Athletics) +
									"m. (Roll: 1d10 = " + String::valueOf(roll) + ")");
									
		creature->sendSystemMessage("Move to your desired destination, using the Last Position waypoint to keep track of your distance. Use the move (rpmove) ability to confirm your movement.");
	}

	static void ConfirmRoleplayMove(CreatureObject* creature) {
		PlayerObject* ghost = creature->getPlayerObject();
		if (ghost == nullptr)
			return;


		// Get previous movement waypoint
		ManagedReference<WaypointObject*> waypoint = ghost->getSurveyWaypoint();
		int distance = GetDistance(creature, waypoint->getPositionX(), waypoint->getPositionZ(), waypoint->getPositionY());
		BorrieRPG::BroadcastMessage(creature, creature->getFirstName() + " moved " + String::valueOf(distance) + " meters from their last position.");
	}
};

#endif /*BORCHARACTER_H_*/
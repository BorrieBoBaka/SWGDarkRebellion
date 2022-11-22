#ifndef BOREFFECT_H_
#define BOREFFECT_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "templates/customization/AssetCustomizationManagerTemplate.h"

#include "system/lang/Long.h"

//#include "templates/roleplay/RoleplayManager.h"
#include "server/zone/borrie/BorrieRPG.h"

class BorEffect : public Logger {
public:
	static void ForceIntoCombat(CreatureObject* creature) {
		ManagedReference<CreatureObject*> target;
		Zone* zone = creature->getZone();
		CreatureManager* creatureManager = zone->getCreatureManager();
		float posX = creature->getPositionX(), posY = creature->getPositionY(), posZ = creature->getPositionZ();
		uint64 parID = creature->getParentID();
		String objName = "", tempName = "vicious_squall";
		uint32 templ = tempName.hashCode();
		uint32 objTempl = objName.length() > 0 ? objName.hashCode() : 0;
		target = creatureManager->spawnCreature(templ, objTempl, posX, posZ, posY, parID);
		Locker clocker(target, creature);
		if (target != nullptr) {
			target->asAiAgent()->activateLoad("");
			target->setDefender(creature);
			creature->setDefender(target);
			target->getThreatMap()->addAggro(creature, 999, 0);
			target->destroyObjectFromWorld(true);
		}
	}

	static void ToggleForceAICombat(CreatureObject* target, CreatureObject* commander) {
		ManagedReference<AiAgent*> agent = target->asAiAgent();
		Locker alock(agent);
		if (agent->getCreatureBitmask() & CreatureFlag::FORCECOMBAT) {
			agent->clearCreatureBit(CreatureFlag::FORCECOMBAT);
			commander->sendSystemMessage("Target is no longer forced into combat.");
		} else {
			agent->setCreatureBit(CreatureFlag::FORCECOMBAT);
			commander->sendSystemMessage("Target will now not peace out of combat.");
		}	
	}

	static void ForceAICombat(CreatureObject* target, CreatureObject* commander) {
		if(target->isAiAgent()) {
			ManagedReference<AiAgent*> agent = target->asAiAgent();
			Locker alock(agent);
			agent->setCreatureBit(CreatureFlag::ALWAYSON);
			agent->setCreatureBit(CreatureFlag::FORCECOMBAT);
		}
		
	}

	static void StopCombat(CreatureObject* creature) {
		//creature->clearCombatState(true);
		Locker lock(creature);
		CombatManager::instance()->forcePeace(creature);
		if(creature->isAiAgent()) {
			creature->asAiAgent()->clearCreatureBit(CreatureFlag::FORCECOMBAT);
			creature->asAiAgent()->clearCreatureBit(CreatureFlag::ALWAYSON);
		}
	}

	static void PlayAnim(CreatureObject* creature, SceneObject* object, bool isAdmin, String animName) {
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
		ManagedReference<CreatureObject*> targetCreature;
		bool isMine;

		if (object == nullptr || !object->isCreatureObject())
			targetCreature = creature;
		else
			targetCreature = object->asCreatureObject();

		if (targetCreature->getPlayerObject() != nullptr) {
			isMine = targetCreature->getPlayerObject()->getAccountID() == ghost->getAccountID();
		} else
			isMine = creature == targetCreature->getLinkedCreature().get();

		if (!isAdmin && !isMine)
			targetCreature = creature;

		targetCreature->doAnimation(animName);
	}

	static void PlayCEF(CreatureObject* creature, SceneObject* object, bool isAdmin, String effectName) {
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
		ManagedReference<CreatureObject*> targetCreature;
		bool isMine;

		if (object == nullptr || !object->isCreatureObject())
			targetCreature = creature;
		else
			targetCreature = object->asCreatureObject();

		if (targetCreature->getPlayerObject() != nullptr) {
			isMine = targetCreature->getPlayerObject()->getAccountID() == ghost->getAccountID();
		} else
			isMine = creature == targetCreature->getLinkedCreature().get();

		if (!isAdmin && !isMine)
			targetCreature = creature;

		targetCreature->playEffect("clienteffect/" + effectName + ".cef");
	}

	static void FauxTargetAttack(CreatureObject* creature, SceneObject* target) {
		ManagedReference<SceneObject*> storedTarget = BorrieRPG::GetStoredObject(creature);

		if (!target->isCreatureObject())
			return;

		if (storedTarget != nullptr) {
			if (storedTarget->getZone() == creature->getZone()) {
				if (storedTarget->isCreatureObject()) {
					uint32 animCRC = GetDefaultAttackAnimation(storedTarget->asTangibleObject(), storedTarget->asCreatureObject()->getWeapon(), 0, 10).hashCode();
					storedTarget->asCreatureObject()->doCombatAnimation(target->asCreatureObject(), animCRC, 0x1, 0x00);
				}
			} else {
				creature->sendSystemMessage("Your current stored target is on the wrong planet.");
			}
		} else {
			creature->sendSystemMessage("Your stored target does not exist or is not set. Use '/dm storetarget' while targeting something to store it.");
		}
	}

	static void PerformReactiveAnimation(CreatureObject* reactor, CreatureObject* reactee, String mode, uint8 hitLocation, bool success) {
		ManagedReference<WeaponObject*> reacteeWeapon = reactee->getWeapon();
		ManagedReference<WeaponObject*> reactorWeapon = reactor->getWeapon();
		uint32 animCRC = GetDefaultAttackAnimation(reactee->asTangibleObject(), reacteeWeapon, hitLocation, 0).hashCode();
		// hitstatus: 0x0-MISS 0x1-HIT 0x2-BLOCK 0x3-DODGE 0x5-COUNTER 0x7-RICOCHET 0x8-REFLECT 0x9-REFLECT_TO_TARGET
		int hitStatus = 0x01;
		if (mode == "defend") {
			if (success)
				hitStatus = 0x02;
		} else if (mode == "dodge") {
			if (success)
				hitStatus = 0x03;
		} else if (mode == "parry") {
			if (!reacteeWeapon->isMeleeWeapon() && reactorWeapon->isJediWeapon()) {
				if (success)
					hitStatus = 0x9;
				else
					hitStatus = 0x08;
			} else {
				if (success)
					hitStatus = 0x05;
			}
		} else if(mode == "miss") {
			hitStatus = 0x0;
		}
		reactee->doCombatAnimation(reactor, animCRC, hitStatus, 0x00);
	}

	static String GetDefaultAttackAnimation(TangibleObject* attacker, WeaponObject* weapon, uint8 hitLocation, int damage) {
		enum lateralLocations { LEFT, CENTER, RIGHT };
		static const char* headLocations[] = {"attack_high_left", "attack_high_center", "attack_high_right"};
		static const char* chestLocations[] = {"attack_mid_left", "attack_mid_center", "attack_mid_right"};
		static const char* legLocations[] = {"attack_low_left", "attack_low_center", "attack_low_right"};

		static const char* rangedAttacks[] = {"fire_1_single", "fire_3_single", "fire_5_single"};

		String intensity = System::random(1) == 1 ? "_medium" : "_light";
		StringBuffer buffer;

		// Yup.
		if (attacker->isDroidObject()) {
			return "droid_attack" + intensity;
		} else if (!attacker->isCreature()) {
			if (weapon->isRangedWeapon()) {
				buffer << rangedAttacks[System::random(2)];

				buffer << intensity;

				if (hitLocation == CombatManager::HIT_HEAD)
					buffer << "_face";

			} else {
				if (hitLocation == 0)
					hitLocation = System::random(5) + 1;

				switch (hitLocation) {
				case CombatManager::HIT_BODY:
					buffer << chestLocations[CENTER];
					break;
				case CombatManager::HIT_LARM:
					buffer << chestLocations[RIGHT];
					break;
				case CombatManager::HIT_RARM:
					buffer << chestLocations[LEFT]; // these are purposely backwards - It's mirrored
					break;
				case CombatManager::HIT_LLEG:
					buffer << legLocations[System::random(1) + 1];
					break;
				case CombatManager::HIT_RLEG:
					buffer << legLocations[System::random(1)];
					break;
				case CombatManager::HIT_HEAD:
					buffer << headLocations[System::random(2)];
					break;
				}

				buffer << intensity;

				// TODO: Actually sequence these
				buffer << "_" << String::valueOf(System::random(3));
			}
		} else {
			if (attacker->getGameObjectType() == SceneObjectType::DROIDCREATURE || attacker->getGameObjectType() == SceneObjectType::PROBOTCREATURE)
				return "droid_attack" + intensity;
			else if (weapon->isRangedWeapon())
				return "creature_attack_ranged" + intensity;
			else
				return "creature_attack" + intensity;
		}

		// info("Generated Attack Animation- " + buffer.toString(), true);
		return buffer.toString();
	}
};

#endif /*BOREFFECT_H_*/
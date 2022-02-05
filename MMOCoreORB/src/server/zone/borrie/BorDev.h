#ifndef BORDEV_H_
#define BORDEV_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/packets/player/PlayMusicMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "templates/customization/AssetCustomizationManagerTemplate.h"
#include "server/zone/managers/combat/CombatManager.h"


#include "server/db/ServerDatabase.h"

class BorDev : public Logger {
public:

	static void SendHelloWorld(CreatureObject* owner) {
		owner->sendSystemMessage("Hello World!");
	}

	static void ToggleCombat(CreatureObject* creature) {
		//Locker clock(target);
		//target->setDefender(target);
		//target->setCombatState();

		ManagedReference<CreatureObject*> target;
		Zone* zone = creature->getZone();
		CreatureManager* creatureManager = zone->getCreatureManager();
		float posX = creature->getPositionX(), posY = creature->getPositionY(), posZ = creature->getPositionZ();
		uint64 parID = creature->getParentID();
		String objName = "", tempName = "vicious_squall";
		uint32 templ = tempName.hashCode();
		uint32 objTempl = objName.length() > 0 ? objName.hashCode() : 0;
		target = creatureManager->spawnCreature(templ, objTempl, posX, posZ, posY, parID);
		if (target != nullptr)
			target->asAiAgent()->activateLoad("");
		Locker clocker(creature);
		Locker targetelocker(target);
		target->setDefender(creature);
		creature->setDefender(target);
		target->getThreatMap()->addAggro(creature, 999, 0);
		target->destroyObjectFromWorld(true);
	}

	static void StopCombat(CreatureObject* creature) {
		//creature->clearCombatState(true);
		Locker lock(creature);
		CombatManager::instance()->forcePeace(creature);
	}

	static void ToggleAlwaysOnAI(CreatureObject* target, CreatureObject* commander) {
		ManagedReference<AiAgent*> agent = target->asAiAgent();
		Locker alock(agent);
		if (agent->getCreatureBitmask() & CreatureFlag::ALWAYSON) {
			agent->clearCreatureBit(CreatureFlag::ALWAYSON);
			commander->sendSystemMessage("Target's AI is no longer always on.");
		} else {
			agent->setCreatureBit(CreatureFlag::ALWAYSON);
			commander->sendSystemMessage("Target's AI is Always On now.");
		}			
	}

	static void ToggleAIWalks(CreatureObject* target, CreatureObject* commander) {
		ManagedReference<AiAgent*> agent = target->asAiAgent();
		Locker alock(agent);
		if (agent->getCreatureBitmask() & CreatureFlag::TOGGLEWALK) {
			agent->clearCreatureBit(CreatureFlag::TOGGLEWALK);
			commander->sendSystemMessage("The target will run if need be.");
		} else {
			agent->setCreatureBit(CreatureFlag::TOGGLEWALK);
			commander->sendSystemMessage("The target is forced to walk.");
		}
	}


	static void SetNPCPosture(CreatureObject* target, int posture) {
		Locker clock(target);
		if (posture == 0)
			target->setPosture(CreaturePosture::UPRIGHT, true, true);
		else if (posture == 1)
			target->setPosture(CreaturePosture::CROUCHED, true, true);
		else if (posture == 2)
			target->setPosture(CreaturePosture::PRONE, true, true);
		else if (posture == 3)
			target->setPosture(CreaturePosture::SNEAKING, true, true);
		else if (posture == 4)
			target->setPosture(CreaturePosture::SITTING, true, true);
		else if (posture == 5)
			target->setPosture(CreaturePosture::KNOCKEDDOWN, true, true);
		else if (posture == 6)
			target->setPosture(CreaturePosture::DEAD, true, true);
		else if (posture == 7)
			target->setPosture(CreaturePosture::CROUCHED, false, true);
		else if (posture == 8)
			target->setPosture(CreaturePosture::CROUCHED, false, false);
	}

	static void ToggleForceAICombat(CreatureObject* target, CreatureObject* commander) {
		ManagedReference<AiAgent*> agent = target->asAiAgent();
		Locker alock(agent);
		if (agent->getCreatureBitmask() & CreatureFlag::FORCECOMBAT) {
			agent->clearCreatureBit(CreatureFlag::FORCECOMBAT);
			commander->sendSystemMessage("Target s no longer forced into combat.");
		} else {
			agent->setCreatureBit(CreatureFlag::FORCECOMBAT);
			commander->sendSystemMessage("Target will now not peace out of combat.");
		}	
	}

	static void ToggleDirectFollow(CreatureObject* target, CreatureObject* commander) {
		ManagedReference<AiAgent*> agent = target->asAiAgent();
		Locker alock(agent);
		if (agent->getCreatureBitmask() & CreatureFlag::DIRECTFOLLOW) {
			agent->clearCreatureBit(CreatureFlag::DIRECTFOLLOW);
			commander->sendSystemMessage("Target will no longer tightly follow you.");
		} else {
			agent->setCreatureBit(CreatureFlag::DIRECTFOLLOW);
			commander->sendSystemMessage("Target will now tightly follow you.");
		}
	}

	static void creatureGoto(CreatureObject* creature, const uint64& target) {
		ManagedReference<SceneObject*> object = creature->getZoneServer()->getObject(target, false);
		if (object == nullptr) {
			creature->sendSystemMessage("Target required for /dm goto commands");
			throw Exception();
		}
		Locker nlocker(object, creature);
		if (object->isCreatureObject()) {
			float x = creature->getPositionX();
			float y = creature->getPositionY();
			float z = creature->getPositionZ();
			CellObject* cell = creature->getParent().get().castTo<CellObject*>();

			object->asCreatureObject()->asAiAgent()->setTargetObject(nullptr);
			object->asCreatureObject()->asAiAgent()->setFollowState(AiAgent::PATROLLING);
			object->asCreatureObject()->asAiAgent()->clearSavedPatrolPoints();
			object->asCreatureObject()->asAiAgent()->stopWaiting();
			object->asCreatureObject()->asAiAgent()->setWait(0);
			object->asCreatureObject()->asAiAgent()->setNextPosition(x, z, y, cell);
			object->asCreatureObject()->asAiAgent()->activateMovementEvent();
		} else {
			creature->sendSystemMessage("Error: Invalid Target. Must be a creature.");
			throw Exception();
		}
	}

	static void SetPosition(CreatureObject* creature, const uint64& target) {
		ManagedReference<SceneObject*> object = creature->getZoneServer()->getObject(target, false);
		object->setPosition(creature->getPositionX(), creature->getPositionZ(), creature->getPositionY());
		object->updateZone(false, false);
	}

	static void creatureFollow(CreatureObject* creature, const uint64& target) {
		ManagedReference<SceneObject*> object = creature->getZoneServer()->getObject(target, false);

		if (object == nullptr) {
			creature->sendSystemMessage("Target required for /dm follow commands");
			throw Exception();
		}
		Locker nlocker(object, creature);
		if (object->isCreatureObject()) {
			object->asCreatureObject()->asAiAgent()->setFollowObject(creature);
			object->asCreatureObject()->asAiAgent()->storeFollowObject();
			object->asCreatureObject()->asAiAgent()->setFollowState(AiAgent::FOLLOWING);
			object->asCreatureObject()->asAiAgent()->stopWaiting();
			object->asCreatureObject()->asAiAgent()->setWait(0);
			object->asCreatureObject()->asAiAgent()->activateMovementEvent();

		} else {
			creature->sendSystemMessage("Error: Invalid Target. Must be a creature.");
			throw Exception();
		}
	}


	static void creatureStay(CreatureObject* creature, const uint64& target) {
		ManagedReference<SceneObject*> object = creature->getZoneServer()->getObject(target, false);

		if (object == nullptr) {
			creature->sendSystemMessage("Target required for /dm retreat commands");
			throw Exception();
		}
		Locker nlocker(object, creature);
		if (object->isCreatureObject()) {
			object->asCreatureObject()->asAiAgent()->setOblivious();
			object->asCreatureObject()->asAiAgent()->setFollowState(AiAgent::OBLIVIOUS);
			object->asCreatureObject()->asAiAgent()->storeFollowObject();
			object->asCreatureObject()->asAiAgent()->setHomeLocation(creature->getPositionX(), creature->getPositionZ(), creature->getPositionY(),
																	 creature->getParent().get().castTo<CellObject*>());
			object->asCreatureObject()->asAiAgent()->stopWaiting();
			object->asCreatureObject()->asAiAgent()->setWait(0);
			object->asCreatureObject()->asAiAgent()->activateMovementEvent();
		} else {
			creature->sendSystemMessage("Error: Invalid Target. Must be a creature.");
			throw Exception();
		}
	}

	static void SetCreatureClient(CreatureObject* creature, const uint64& target) {
		ManagedReference<SceneObject*> object = creature->getZoneServer()->getObject(target, false);

		if (object == nullptr) {
			creature->sendSystemMessage("Target required for /dm retreat commands");
			throw Exception();
		}
		Locker nlocker(object, creature);
		if (object->isCreatureObject()) {
			object->asCreatureObject()->setClient(creature->getClient());
			creature->getClient()->setPlayer(object->asCreatureObject());
		}
	}

	static void EquipNPCWeapon(SceneObject* target, bool forceRanged) {
		if (target->isCreatureObject()) {
			if (target->asCreatureObject()->asAiAgent() != nullptr) {
				Locker nlocker(target);
				target->asCreatureObject()->asAiAgent()->selectWeapon(forceRanged);
			}
		}
	}



};

#endif 
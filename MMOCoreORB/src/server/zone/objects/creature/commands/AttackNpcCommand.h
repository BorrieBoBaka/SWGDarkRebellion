/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ATTACKNPCCOMMAND_H_
#define ATTACKNPCCOMMAND_H_

#include "server/zone/borrie/BorCombat.h"

class AttackNpcCommand : public QueueCommand {

public:
	AttackNpcCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		uint64 storedTarget = creature->getStoredLong("storedtarget");

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		int adminLevelCheck = ghost->getAdminLevel();

		if (creature->getStoredInt("secretdm") == 1) {
			adminLevelCheck = 15;
		}

		if(adminLevelCheck < 1) {
			creature->sendSystemMessage("You don't have the right permissions to do that.");
			return SUCCESS;
		}

		ManagedReference<SceneObject*> object;
		if (target != 0) {
			object = server->getZoneServer()->getObject(target, false);
		} else {
			creature->sendSystemMessage("You need a target to attack!");
			return SUCCESS;
		}

		ManagedReference<SceneObject*> storedObject;
		if (storedTarget != 0) {
			storedObject = server->getZoneServer()->getObject(storedTarget, false);
		} else {
			creature->sendSystemMessage("You need a stored target to be the attacker!");
			return SUCCESS;
		}

		ManagedReference<CreatureObject*> targetCreature;

		if (object->isCreatureObject()) {
			targetCreature = object->asCreatureObject();
		} else {
			creature->sendSystemMessage("You need a target to attack!");
			return SUCCESS;
		}

		ManagedReference<CreatureObject*> storedTargetCreature;

		if (storedObject->isCreatureObject()) {
			storedTargetCreature = storedObject->asCreatureObject();
		} else {
			creature->sendSystemMessage("You need a stored target to be the attacker!");
			return SUCCESS;
		}

		StringTokenizer args(arguments.toString());

		String command;

		if (args.hasMoreTokens()) {
			args.getStringToken(command);
			if(command == "faux") {
				BorEffect::PerformReactiveAnimation(storedTargetCreature, targetCreature, "hit", CombatManager::HIT_BODY, true);
			} else if (command == "power") {

			} else if(command == "flurry") {

			} else if(command == "aimed") {

			}
		} else {
			BorCombat::AttackTarget(storedTargetCreature, targetCreature, creature, -1, false);
		}

		return SUCCESS;
	}

};

#endif 

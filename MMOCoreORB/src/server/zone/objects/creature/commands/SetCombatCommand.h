/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETCOMBATCOMMAND_H_
#define SETCOMBATCOMMAND_H_

#include "server/zone/borrie/BorEffect.h"

class SetCombatCommand : public QueueCommand {

public:
	SetCombatCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		int adminLevelCheck = ghost->getAdminLevel();

		StringTokenizer args(arguments.toString());

		if(adminLevelCheck > 0) {
			ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);
			ManagedReference<CreatureObject*> targetCreature; // The Target Object as a Creature
			if(targetObject != nullptr) {
				if (targetObject->isCreatureObject()) {
					targetCreature = targetObject->asCreatureObject();
					if(targetCreature->isPlayerCreature()) {
						//Make target into combat
						BorEffect::ForceIntoCombat(targetCreature);
					} else {
						//use NPC method
						if(targetCreature->isInCombat()) {
							BorEffect::StopCombat(targetCreature);
						} else {
							BorEffect::ForceAICombat(targetCreature, creature);
							BorEffect::ForceIntoCombat(targetCreature);
						}	
					}
				} else {
					//Set my own combat state.
					BorEffect::ForceIntoCombat(creature);
				}
			} else {
				//Set my own combat state.
				BorEffect::ForceIntoCombat(creature);
			}
		} else {
			//Set my own combat state
			BorEffect::ForceIntoCombat(creature);
		}
		return SUCCESS;
	}

};

#endif 

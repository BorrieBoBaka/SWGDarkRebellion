/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NFOLLOWCOMMAND_H_
#define NFOLLOWCOMMAND_H_

#include "server/zone/borrie/BorNPC.h"

class NFollowCommand : public QueueCommand {

public:
	NFollowCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
		
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

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);
		ManagedReference<CreatureObject*> targetCreature; // The Target Object as a Creature

		bool hasOwnership = false;

		if (targetObject != nullptr) {
			if (targetObject->isCreatureObject())
				targetCreature = targetObject->asCreatureObject();
			else {
				creature->sendSystemMessage("Invalid target. Target must be a creature you have ownership over.");
				return INVALIDTARGET;
			}

			if (adminLevelCheck > 0) {
				hasOwnership = true;
			} else {
				if (targetCreature->isPlayerCreature()) {
					if (targetCreature->getPlayerObject()->getAccountID() == ghost->getAccountID()) {
						hasOwnership = true;
					}
				} else if (targetCreature->isPet()) {
					ManagedReference<CreatureObject*> owner = targetCreature->getLinkedCreature().get();
					if (creature->getObjectID() == owner->getObjectID()) {
						hasOwnership = true;
					}
				}
			}

			if (hasOwnership) {
				// Execute Command
				String command;
				if (args.hasMoreTokens()) {
					args.getStringToken(command);
					command = command.toLowerCase();
					if (command == "direct") {
						// Toggle Direct Follow
						BorNPC::ToggleDirectFollow(targetCreature, creature);
					} else if (command == "stop") {
						// Stay
						BorNPC::SendCreatureToPosition(targetCreature, creature);
					} else if (command == "return") {
						// Drop follow, return home.
						BorNPC::SetCreatureStay(targetCreature, creature);
					} else if(command == "walk") { 
						BorNPC::ToggleAIWalks(targetObject->asCreatureObject(), creature);					
					}
				} else {
					BorNPC::SetCreatureFollow(targetCreature, creature);
				}

			} else {
				creature->sendSystemMessage("Invalid target. You don't have permission to do that to this target. You must be the owner of the creature.");
				return INVALIDTARGET;
			}

		} else {
			creature->sendSystemMessage("Invalid target. Need a target to begin with.");
			return INVALIDTARGET;
		}
		return SUCCESS;
	}

};

#endif 

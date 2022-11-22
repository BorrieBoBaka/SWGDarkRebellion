/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANIMCOMMAND_H_
#define ANIMCOMMAND_H_

#include "server/zone/borrie/BorEffect.h"

class AnimCommand : public QueueCommand {

public:
	AnimCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

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

		ManagedReference<SceneObject*> object;			  // The Target Object
		ManagedReference<CreatureObject*> targetCreature; // The Target Object as a Creature

		// If we're admin, perform the animation on the target.
		if (target != 0 && adminLevelCheck > 0) {
			object = server->getZoneServer()->getObject(target, false);
			if (object->isCreatureObject())
				targetCreature = object->asCreatureObject();
			else
				targetCreature = creature;
		} else
			targetCreature = creature;

		
		//If we're admin, perform the animation on the target.

		String command;
		if (args.hasMoreTokens()) {
			args.getStringToken(command);
			command = command.toLowerCase();
			BorEffect::PlayAnim(creature, targetCreature, adminLevelCheck > 0, command);
		} else {
			// If no arguments, pull up a list of all anims, with custom option at the top
		}

		return SUCCESS;
	}

};

#endif 

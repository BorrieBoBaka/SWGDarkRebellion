/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
        
        
        Original file from Empire in Flames
        https://www.empireinflames.com/

        https://gitlab.com/Halyn/EiF-Public/-/blob/unstable/MMOCoreORB/src/server/zone/objects/creature/commands/StowCommand.h

        */

#ifndef STOWCOMMAND_H_
#define STOWCOMMAND_H_

#include "server/zone/objects/creature/events/StowTask.h"

class StowCommand : public QueueCommand {
public:

	StowCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->isInCombat()) {
			creature->sendSystemMessage("You cannot use a utility device in combat!");
			return GENERALERROR;
		}
		
		Reference<Task*> pendingTask = creature->getPendingTask("holster");
		if (pendingTask != nullptr)
			return SUCCESS;

		pendingTask = creature->getPendingTask("unholster");
		if (pendingTask != nullptr)
			return SUCCESS;
		
		pendingTask = creature->getPendingTask("stow");
		if (pendingTask != nullptr)
			return SUCCESS;

		pendingTask = creature->getPendingTask("unstow");
		if (pendingTask != nullptr)
			return SUCCESS;
		
		pendingTask = creature->getPendingTask("shoulder");
		if (pendingTask != nullptr)
			return SUCCESS;

		pendingTask = creature->getPendingTask("unshoulder");
		if (pendingTask != nullptr)
			return SUCCESS;

		ManagedReference<TangibleObject*> heldDevice = creature->getSlottedObject("hold_r").castTo<TangibleObject*>();
		if (heldDevice != nullptr)
			return SUCCESS;

		heldDevice = creature->getSlottedObject("hold_l").castTo<TangibleObject*>();
		ManagedReference<TangibleObject*> stowedDevice = creature->getSlottedObject("utility").castTo<TangibleObject*>();
		if (stowedDevice != nullptr) {
			creature->doAnimation("draw_utility");
			Reference<Task*> task = new StowTask(creature, stowedDevice);
			creature->addPendingTask("unstow", task, 850);
		} else if (heldDevice != nullptr) {
			creature->doAnimation("stow_utility");
			Reference<Task*> task = new StowTask(creature, heldDevice);
			creature->addPendingTask("stow", task, 500);
		}

		// creature->info("transfer item command");
		return SUCCESS;
	}

};

#endif //STOWCOMMAND_H_
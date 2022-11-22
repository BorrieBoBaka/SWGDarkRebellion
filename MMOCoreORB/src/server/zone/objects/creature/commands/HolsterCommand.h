/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
        
        Original file from Empire in Flames
        https://www.empireinflames.com/

        https://gitlab.com/Halyn/EiF-Public/-/blob/unstable/MMOCoreORB/src/server/zone/objects/creature/commands/HolsterCommand.h
        */

#ifndef HOLSTERCOMMAND_H_
#define HOLSTERCOMMAND_H_

#include "server/zone/objects/creature/events/HolsterTask.h"

class HolsterCommand : public QueueCommand {
public:

	HolsterCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->isInCombat()) {
			creature->sendSystemMessage("You cannot holster a weapon in combat!");
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

		ManagedReference<WeaponObject*> heldWeapon = creature->getSlottedObject("hold_r").castTo<WeaponObject*>();
		ManagedReference<WeaponObject*> holsteredWeapon = creature->getHolsteredWeapon("holster");
		if (holsteredWeapon != nullptr) {
			for (int j = 0; j < holsteredWeapon->getArrangementDescriptorSize(); ++j) {
				const Vector<String>* descriptors = holsteredWeapon->getArrangementDescriptor(j);
				for (int k = 0; k < descriptors->size(); ++k) {
					const String& descriptorName = descriptors->get(k);
					if (descriptorName == "hip_holster_melee" || descriptorName == "hip_holster_gun" || descriptorName == "hip_holster_melee_reverse") {
						creature->doAnimation("draw_holster");
						Reference<Task*> task = new HolsterTask(creature, holsteredWeapon);
						creature->addPendingTask("unholster", task, 100);
					}
					if (descriptorName == "back_holster_melee" || descriptorName == "back_holster_gun" || descriptorName == "back_holster_melee_alt" || descriptorName == "back_holster_gun_alt") {
						creature->doAnimation("draw_pack");
						Reference<Task*> task = new HolsterTask(creature, holsteredWeapon);
						creature->addPendingTask("unholster", task, 500);
					}
				}
			}
		} else if (heldWeapon != nullptr) {
			for (int j = 0; j < heldWeapon->getArrangementDescriptorSize(); ++j) {
				const Vector<String>* descriptors = heldWeapon->getArrangementDescriptor(j);
				for (int k = 0; k < descriptors->size(); ++k) {
					const String& descriptorName = descriptors->get(k);
					if (descriptorName == "hip_holster_melee" || descriptorName == "hip_holster_gun" || descriptorName == "hip_holster_melee_reverse") {
						creature->doAnimation("stow_holster");
						Reference<Task*> task = new HolsterTask(creature, heldWeapon);
						creature->addPendingTask("holster", task, 500);
					}
					if (descriptorName == "back_holster_melee" || descriptorName == "back_holster_gun" || descriptorName == "back_holster_melee_alt" || descriptorName == "back_holster_gun_alt") {
						creature->doAnimation("stow_pack");
						Reference<Task*> task = new HolsterTask(creature, heldWeapon);
						creature->addPendingTask("holster", task, 500);
					}
				}
			}
		}

		// creature->info("transfer item command");
		return SUCCESS;
	}

};

#endif //HOLSTERCOMMAND_H_
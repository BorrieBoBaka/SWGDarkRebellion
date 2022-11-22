/*
 * HolsterTask.h
    
    Original file from Empire in Flames
    https://www.empireinflames.com/

    https://gitlab.com/Halyn/EiF-Public/-/blob/unstable/MMOCoreORB/src/server/zone/objects/creature/events/HolsterTask.h
 */

#ifndef HOLSTERTASK_H_
#define HOLSTERTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

class HolsterTask : public Task {
	ManagedReference<CreatureObject*> creature;
	ManagedReference<WeaponObject*> weapon;
public:
	HolsterTask(CreatureObject* creo, WeaponObject* heldWeapon) {
		creature = creo;
		weapon = heldWeapon;
	}

	void run() {
		Reference<Task*> pendingTask = creature->getPendingTask("holster");
		if (pendingTask != nullptr) {
			Locker locker(creature);
			if (creature->isNonPlayerCreatureObject())
				weapon->npcHolsterWeapon(creature);
			else
				weapon->holsterWeapon(creature);
			creature->removePendingTask("holster");
		}
		pendingTask = creature->getPendingTask("unholster");
		if (pendingTask != nullptr) {
			Locker locker(creature);
			weapon->unholsterWeapon(creature);
			creature->removePendingTask("unholster");
		}
	}
};

#endif /* ANIMATIONTASK_H_ */
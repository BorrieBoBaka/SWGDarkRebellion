/*
 * StowTask.h

    Original file from Empire in Flames
    https://www.empireinflames.com/

    https://gitlab.com/Halyn/EiF-Public/-/blob/unstable/MMOCoreORB/src/server/zone/objects/creature/events/StowTask.h
 */

#ifndef STOWTASK_H_
#define STOWTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"

class StowTask : public Task {
	ManagedReference<CreatureObject*> creature;
	ManagedReference<TangibleObject*> utility;
public:
	StowTask(CreatureObject* creo, TangibleObject* heldUtility) {
		creature = creo;
		utility = heldUtility;
	}

	void run() {
		Reference<Task*> pendingTask = creature->getPendingTask("stow");
		if (pendingTask != nullptr) {
			Locker locker(creature);
			utility->stowObject(creature);
			creature->removePendingTask("stow");
		}
		pendingTask = creature->getPendingTask("unstow");
		if (pendingTask != nullptr) {
			Locker locker(creature);
			utility->unstowObject(creature);
			creature->removePendingTask("unstow");
		}
	}
};

#endif /* ANIMATIONTASK_H_ */
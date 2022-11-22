/*
 * SetNameCallback.h
 *
 *  Created on: May 13, 2022
 *      Author: Borrie BoBaka
 */

#ifndef SETNAMECALLBACK_H_
#define SETNAMECALLBACK_H_
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/Zone.h"


class SetNameCallback : public SuiCallback {
	ManagedWeakReference<ZoneServer*> server;
	ManagedWeakReference<SceneObject*> target;

public:
	SetNameCallback(ZoneServer* serv, SceneObject* target) : SuiCallback(serv) {
		this->server = serv;
		this->target = target;
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if(cancelPressed || server == nullptr)
			return;

		ManagedReference<SceneObject*> targetObject = target.get();
		if(targetObject == nullptr)
			return;

		ManagedReference<ZoneServer*> zone = this->server.get();
		if (zone == nullptr)
			return;

		PlayerObject* ghost = creature->getPlayerObject();
		if (ghost == nullptr)
			return;

		String name = args->get(0).toString();

        targetObject->setCustomObjectName(name, true);

		creature->sendSystemMessage("Object Renamed."); 
	}
};




#endif /* SETNAMECALLBACK_H_ */

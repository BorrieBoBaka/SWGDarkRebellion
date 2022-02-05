/*
 * SetDescriptionCallback.h
 *
 *  Created on: Jan 22, 2022
 *      Author: Borrie BoBaka
 */

#ifndef SETDESCRIPTIONCALLBACK_H_
#define SETDESCRIPTIONCALLBACK_H_
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/Zone.h"


class SetDescriptionCallback : public SuiCallback {
	ManagedWeakReference<ZoneServer*> server;
	ManagedWeakReference<SceneObject*> target;

public:
	SetDescriptionCallback(ZoneServer* serv, SceneObject* target) : SuiCallback(serv) {
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

		String description = args->get(0).toString();

        targetObject->setStoredString("rp_description", description);

		creature->sendSystemMessage("Description updated."); 
	}
};




#endif /* SETDESCRIPTIONCALLBACK_H_ */

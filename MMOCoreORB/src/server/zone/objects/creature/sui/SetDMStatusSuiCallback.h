/*
 * SetDMStatusSuiCallback.h
 *
 *  Created on: Feb. 24, 2022
 *      Author: Borrie BoBaka
 */

#ifndef SETDMSTATUSSUICALLBACK_H_
#define SETDMSTATUSSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class SetDMStatusSuiCallback : public SuiCallback {
public:
	SetDMStatusSuiCallback(ZoneServer* serv) : SuiCallback(serv) {

	}

	void run(CreatureObject* player, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed) {
			
			return;
		}

        String status = args->get(0).toString();

        player->setStoredString("rp_dm_status", status);
        player->sendSystemMessage("Your DM status has been set!");
		
	}
};

#endif /* SETDMSTATUSSUICALLBACK_H_ */

/*
 * RpShipDeedImplementation.cpp
 *
 *  Created on: 10/6/2022
 *      Author: Borrie BoBaka
 */

#include "server/zone/objects/tangible/deed/rp_ship/RpShipDeed.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "templates/tangible/RpShipDeedTemplate.h"
#include "server/zone/objects/intangible/RpShipControlDevice.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/structure/StructureManager.h"

void RpShipDeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	DeedImplementation::loadTemplateData(templateData);

	RpShipDeedTemplate* deedData = dynamic_cast<RpShipDeedTemplate*>(templateData);

	if (deedData == nullptr)
		return;

	controlDeviceObjectTemplate = deedData->getControlDeviceObjectTemplate();
	appearanceMobile = deedData->getAppearanceMobile();
	landFlatteningPoint = deedData->getLandFlatteningPoint();
}

void RpShipDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	DeedImplementation::fillAttributeList(alm, object);
}

void RpShipDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	setLoggingName("RpShipDeed");
}

void RpShipDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, player);

	if (isASubChildOf(player))
		menuResponse->addRadialMenuItem(20, 3, "@rp_ship:menu_generate");
}

int RpShipDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID == 20) {
		if (generated || !isASubChildOf(player))
			return 1;

		ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

		if (datapad == nullptr) {
			player->sendSystemMessage("Datapad doesn't exist when trying to create ship");
			return 1;
		}

		// Check if this will exceed maximum number of vehicles allowed
		ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();

		int shipsInDatapad = 0;
		int maxStoredShips = playerManager->getBaseStoredRpShips();

		for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
			Reference<SceneObject*> obj =  datapad->getContainerObject(i).castTo<SceneObject*>();

			if (obj != nullptr && obj->isRpShipControlDevice() )
				shipsInDatapad++;

		}

		if (shipsInDatapad >= maxStoredShips) {
			player->sendSystemMessage("You already have the maximum number of ships that you can own."); // You already have the maximum number of vehicles that you can own.
			return 1;
		}

        Reference<RpShipControlDevice*> rpShipControlDevice = (server->getZoneServer()->createObject(controlDeviceObjectTemplate.hashCode(), 1)).castTo<RpShipControlDevice*>();

        if(rpShipControlDevice == nullptr) {
            player->sendSystemMessage("wrong rp ship control device object template " + controlDeviceObjectTemplate);
			return 1;
        }

        Locker locker(rpShipControlDevice);

		if(generatedObjectTemplate != "") {
			Reference<DirectorManager*> realDirectorManager = DirectorManager::instance();

        	String globalShipCountString = realDirectorManager->getQuestStatus("player_rp_ship_count");
        	int globalShipCount = 0;
        	if(globalShipCountString != "")
        	    globalShipCount = Integer::valueOf(globalShipCountString);

        	int newShipID = globalShipCount + 1;
        	float x = (fmod((float)newShipID, 100.0f) * 140.0f) - 7000.0f;
        	float y = (((float)newShipID / 100.0f) * 140.0f) - 7000.0f;

        	Zone* zone = server->getZoneServer()->getZone("rp_ship_a");

        	StructureObject* structure = StructureManager::instance()->placeStructure(player, zone, generatedObjectTemplate, x, y, 0, 1);

        	if (structure == nullptr) {
        	    rpShipControlDevice->destroyObjectFromDatabase(true);
				player->sendSystemMessage("wrong ship building object template " + generatedObjectTemplate);
				return 1;
        	}

        	structure->setStoredInt("ship_id", newShipID);
        	rpShipControlDevice->setStoredLong("structure", structure->getObjectID());
        	realDirectorManager->setQuestStatus("player_rp_ship_count", String::valueOf(newShipID));

        	Locker vlocker(structure, player);
		}        

		//Set other vars
		rpShipControlDevice->setStoredString("appearanceMobile", appearanceMobile);
		rpShipControlDevice->setStoredString("flatteningTemplate", landFlatteningPoint);

		if (datapad->transferObject(rpShipControlDevice, -1)) {
			datapad->broadcastObject(rpShipControlDevice, true);

			generated = true;

			destroyObjectFromWorld(true);
			destroyObjectFromDatabase(true);

            player->sendSystemMessage("Ship initialized. Control device is now available on your datapad. Happy flying.");

			return 0;
		} else {
			rpShipControlDevice->destroyObjectFromDatabase(true);
            player->sendSystemMessage("An issue occured while initializing your starship. Please see the manufacturerer.");
			return 1;
		}
    }
	return DeedImplementation::handleObjectMenuSelect(player, selectedID);
}
/*
 * RpShipControlDeviceImplementation.cpp
 *
 *  Created on: 10/06/2022
 *      Author: BorrieBoBaka
 */

#include "server/zone/objects/intangible/RpShipControlDevice.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/creature/events/VehicleDecayTask.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/player/sessions/TradeSession.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "templates/building/SharedBuildingObjectTemplate.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/director/DirectorManager.h"


void RpShipControlDeviceImplementation::spawnCaller(CreatureObject* player) {

}

void RpShipControlDeviceImplementation::landShip(CreatureObject* player) {

}

void RpShipControlDeviceImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {

    //Destroy structure then object itself. 

    bool isBuildingShip = getStoredLong("structure") != 0;

    if(isBuildingShip) {
        long shipID = getStoredLong("structure");
        ManagedReference<BuildingObject*> shipBuilding = getZoneServer()->getObject(shipID).castTo<BuildingObject*>();

        if(shipBuilding != nullptr) {
            //Add to Empty Structure Slots
            int shipID = shipBuilding->getStoredInt("ship_id");
            int emptyShipSlots = Integer::valueOf(DirectorManager::instance()->getQuestStatus("player_rp_ship_empty_count"));
            DirectorManager::instance()->setQuestStatus("player_rp_ship_empty_index_" + String::valueOf(emptyShipSlots + 1), String::valueOf(shipID));
            DirectorManager::instance()->setQuestStatus("player_rp_ship_empty_count", String::valueOf(emptyShipSlots + 1));

            for (uint32 i = 1; i <= shipBuilding->getTotalCellNumber(); ++i) {
            ManagedReference<CellObject*> cellObject = shipBuilding->getCell(i);

            if (cellObject == nullptr)
					continue;

			    int childObjects = cellObject->getContainerObjectsSize();

			    if (childObjects > 0) {
                    for (int j = childObjects - 1; j >= 0; --j) {
                        ManagedReference<SceneObject*> obj = cellObject->getContainerObject(j);

					    if (obj->isPlayerCreature() || obj->isPet()) {
                            CreatureObject* playerCreature = cast<CreatureObject*>(obj.get());
                            //shipBuilding->unlock();

						    try {
							    Locker plocker(playerCreature);

							    //playerCreature->teleport(x, z, y, 0);
                                //TODO: This should be the ship's last landing point.
                                playerCreature->switchZone("rp_tatooine", 1070, 0, 64, 0);
						    } catch (...) {
							    playerCreature->error("unreported exception caught while teleporting");
						    }

						    //shipBuilding->wlock();
                        }
                    }
                }				
            }
            //Pop the structure
            StructureManager::instance()->destroyStructure(shipBuilding, false);
        } else {
            //player->sendSystemMessage("No ship was found connected to this device. Clearing device from your datapad...");
        }
    }

	IntangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

int RpShipControlDeviceImplementation::canBeDestroyed(CreatureObject* player) {

    bool isBuildingShip = getStoredLong("structure") != 0;;

    //Check to see if the ship has anyone onboard
    //Check to see if the ship has any objects in it

    if(isBuildingShip) {
        uint64 shipID = getStoredLong("structure");
        ManagedReference<BuildingObject*> shipBuilding = player->getZoneServer()->getObject(shipID).castTo<BuildingObject*>();

        if(shipBuilding == nullptr) {
            //player->sendSystemMessage("No ship structure was even found. Clearing Control Device from Datapad...");
            return IntangibleObjectImplementation::canBeDestroyed(player);
        }

        if(shipBuilding->getCurrentNumberOfPlayerItems() > 0) {
            player->sendSystemMessage("You can't scuttle a ship when it has items in it!");
            return 1;
        }

        //If Ship is Landed
        uint64 stateValue = DirectorManager::instance()->readSharedMemory(String::valueOf(shipID) + ":landShip:shipStatus");
        if(stateValue != 0) {
            player->sendSystemMessage("You can't scuttle a ship while it's landed somewhere!");
            return 1;
        }            
    }

	return IntangibleObjectImplementation::canBeDestroyed(player);
}

bool RpShipControlDeviceImplementation::canBeTradedTo(CreatureObject* player, CreatureObject* receiver, int numberInTrade) {
	ManagedReference<SceneObject*> datapad = receiver->getSlottedObject("datapad");

	if (datapad == nullptr)
		return false;

	ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();

	int shipsInDatapad = numberInTrade;
	int maxStoredShips = playerManager->getBaseStoredRpShips();

	for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
		Reference<SceneObject*> obj =  datapad->getContainerObject(i).castTo<SceneObject*>();

		if (obj != nullptr && obj->isRpShipControlDevice() ){
			shipsInDatapad++;
		}
	}

	if( shipsInDatapad >= maxStoredShips){
		player->sendSystemMessage("That person has too many ships in their datapad");
		receiver->sendSystemMessage("You already have the maximum number of ships that you can own."); // You already have the maximum number of vehicles that you can own.
		return false;
	}

	return true;
}

/*
void RpShipControlDeviceImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (isASubChildOf(player)) {
        menuResponse->addRadialMenuItem(80, 3, "@rp_ship:board_ship");
        menuResponse->addRadialMenuItem(81, 3, "@rp_ship:land_ship");
        menuResponse->addRadialMenuItem(82, 3, "@rp_ship:generate_caller");
        menuResponse->addRadialMenuItem(83, 3, "@rp_ship:rename_ship");
    }
		
}

int RpShipControlDeviceImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
    if (selectedID == 80)  { //Board Ship
        long shipID = getStoredLong("structure");
        ManagedReference<BuildingObject*> shipBuilding = player->getZoneServer()->getObject(shipID).castTo<BuildingObject*>();
        
        if(shipBuilding == nullptr) {
            player->sendSystemMessage("An error occured. Jawas have stolen your ship!");
            return 1;
        }

        Reference<SharedBuildingObjectTemplate*> shipTemplate = dynamic_cast<SharedBuildingObjectTemplate*>(shipBuilding->getObjectTemplate());

        Vector3 entrancePoint = shipTemplate->getEntrancePoint();
        int entranceCell = shipTemplate->getEntranceCell();
        Zone* shipZone = shipBuilding->getZone();
        CellObject* cell = shipBuilding->getCell(entranceCell);

        //player->sendSystemMessage("Debug Ship ID: " + String::valueOf(shipBuilding->getObjectID()) + " Cell: " + String::valueOf(entranceCell));

        if(cell == nullptr) {
            player->sendSystemMessage("Could not find a valid entrance point for your ship.");
            return 1;
        }

        uint64 cellID = shipBuilding->getCell(entranceCell)->getObjectID();
        
        //player->sendSystemMessage("realCellID: " + String::valueOf(cellID));
        player->switchZone(shipZone->getZoneName(), entrancePoint.getX(), entrancePoint.getZ(), entrancePoint.getY(), cellID);
    } else if(selectedID == 81) { //Land Ship

    } else if(selectedID == 82) { //Generate Caller

    } else if(selectedID == 83) { //Rename Ship

    }


    return 0;
}
*/

void RpShipControlDeviceImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	SceneObjectImplementation::fillAttributeList(alm, object);
    //alm->insertAttribute("test", 1);
}
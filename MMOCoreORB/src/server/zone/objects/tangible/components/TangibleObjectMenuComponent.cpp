/*
 * TangibleObjectMenuComponent.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "TangibleObjectMenuComponent.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/sui/colorbox/SuiColorBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/callbacks/ColorArmorSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/SetDescriptionCallback.h"
#include "server/zone/objects/player/sui/callbacks/SetNameCallback.h"
#include "server/zone/ZoneServer.h"
#include "templates/customization/AssetCustomizationManagerTemplate.h"
#include "server/zone/borrie/BorrieRPG.h"

void TangibleObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	ObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	uint32 gameObjectType = sceneObject->getGameObjectType();

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>( sceneObject);

	/*
	// Figure out what the object is and if its able to be Sliced.
	if(tano->isSliceable() && !tano->isSecurityTerminal()) { // Check to see if the player has the correct skill level

		bool hasSkill = true;
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		if ((gameObjectType == SceneObjectType::PLAYERLOOTCRATE) && !player->hasSkill("combat_smuggler_novice"))
			hasSkill = false;
		else if (sceneObject->isContainerObject())
			hasSkill = false; // Let the container handle our slice menu
		else if (sceneObject->isMissionTerminal() && !player->hasSkill("combat_smuggler_slicing_01"))
			hasSkill = false;
		else if (sceneObject->isWeaponObject() && (!inventory->hasObjectInContainer(sceneObject->getObjectID()) || !player->hasSkill("combat_smuggler_slicing_02")))
			hasSkill = false;
		else if (sceneObject->isArmorObject() && (!inventory->hasObjectInContainer(sceneObject->getObjectID()) || !player->hasSkill("combat_smuggler_slicing_03")))
			hasSkill = false;

		if(hasSkill)
			menuResponse->addRadialMenuItem(69, 3, "@slicing/slicing:slice"); // Slice
	} */

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory->hasObjectInContainer(sceneObject->getObjectID())) {
		if(!sceneObject->isWeaponObject() || player->getPlayerObject()->hasGodMode()) {
			menuResponse->addRadialMenuItem(81, 3, "Change Color");
			menuResponse->addRadialMenuItemToRadialID(81, 82, 3, "Primary");
			menuResponse->addRadialMenuItemToRadialID(81, 83, 3, "Secondary");
			menuResponse->addRadialMenuItemToRadialID(81, 84, 3, "Tertiary");
		}	

		if(player->getPlayerObject()->hasGodMode()) {
			menuResponse->addRadialMenuItem(91, 3, "DM Options");
			menuResponse->addRadialMenuItemToRadialID(91, 92, 3, "Set Description");
			menuResponse->addRadialMenuItemToRadialID(91, 93, 3, "Set Writeable");
			menuResponse->addRadialMenuItemToRadialID(91, 94, 3, "Copy Object");
			menuResponse->addRadialMenuItemToRadialID(91, 95, 3, "Rename Object");
			menuResponse->addRadialMenuItemToRadialID(91, 96, 3, "Give to Target");
			menuResponse->addRadialMenuItemToRadialID(91, 97, 3, "Set as Mount");
		}
	}

	

	//WearableObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player); 	

	if(player->getPlayerObject() != nullptr && player->getPlayerObject()->isPrivileged()) {
		/// Viewing components used to craft item, for admins
		ManagedReference<SceneObject*> container = tano->getSlottedObject("crafted_components");
		if(container != nullptr) {

			if(container->getContainerObjectsSize() > 0) {

				SceneObject* satchel = container->getContainerObject(0);

				if(satchel != nullptr && satchel->getContainerObjectsSize() > 0) {
					menuResponse->addRadialMenuItem(79, 3, "@ui_radial:ship_manage_components"); // View Components
				}
			}
		}
	}

	ManagedReference<SceneObject*> parent = tano->getParent().get();
	if (parent != nullptr && parent->getGameObjectType() == SceneObjectType::STATICLOOTCONTAINER) {
		menuResponse->addRadialMenuItem(10, 3, "@ui_radial:item_pickup"); //Pick up
	}
}

int TangibleObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isTangibleObject())
		return 0;

	TangibleObject* tano = cast<TangibleObject*>( sceneObject);


	if (selectedID == 69 && player->hasSkill("combat_smuggler_novice") ) { // Slice [PlayerLootCrate]
		if (player->containsActiveSession(SessionFacadeType::SLICING)) {
			player->sendSystemMessage("@slicing/slicing:already_slicing");
			return 0;
		}

		//Create Session
		ManagedReference<SlicingSession*> session = new SlicingSession(player);
		session->initalizeSlicingMenu(player, tano);

		return 0;
	} else if (selectedID == 79) { // See components (admin)
		if(player->getPlayerObject() != nullptr && player->getPlayerObject()->isPrivileged()) {

			SceneObject* container = tano->getSlottedObject("crafted_components");
			if(container != nullptr) {

				if(container->getContainerObjectsSize() > 0) {

					SceneObject* satchel = container->getContainerObject(0);

					if(satchel != nullptr) {

						satchel->sendWithoutContainerObjectsTo(player);
						satchel->openContainerTo(player);

					} else {
						player->sendSystemMessage("There is no satchel this container");
					}
				} else {
					player->sendSystemMessage("There are no items in this container");
				}
			} else {
				player->sendSystemMessage("There is no component container in this object");
			}
		}

		return 0;
	}
	if (selectedID == 82 || selectedID == 83 || selectedID == 84) {
		ManagedReference<SceneObject*> parent = sceneObject->getParent().get();

		if (parent == nullptr)
			return 0;

		if (parent->isPlayerCreature()) {
			player->sendSystemMessage("@armor_rehue:equipped");
			return 0;
		}

		if (parent->isCellObject()) {
			ManagedReference<SceneObject*> obj = parent->getParent().get();

			if (obj != nullptr && obj->isBuildingObject()) {
				ManagedReference<BuildingObject*> buio = cast<BuildingObject*>(obj.get());

				if (!buio->isOnAdminList(player))
					return 0;
			}
		} else {
			if (!sceneObject->isASubChildOf(player))
				return 0;
		}

		ZoneServer* server = player->getZoneServer();

		if (server != nullptr) {
			// The color index.
			String appearanceFilename = sceneObject->getObjectTemplate()->getAppearanceFilename();
			VectorMap<String, Reference<CustomizationVariable*>> variables;
			AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(appearanceFilename.hashCode(), variables, false);

			int paletteID = 0;
			if (selectedID == 83)
				paletteID = 1;
			else if (selectedID == 84)
				paletteID = 2;

			// The Sui Box.
			ManagedReference<SuiColorBox*> cbox = new SuiColorBox(player, SuiWindowType::COLOR_ARMOR);
			cbox->setCallback(new ColorArmorSuiCallback(server));
			cbox->setColorPalette(variables.elementAt(paletteID).getKey()); 
			cbox->setUsingObject(sceneObject);

			// Add to player.
			ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
			ghost->addSuiBox(cbox);
			player->sendMessage(cbox->generateMessage());
		}
	} 

	if(selectedID == 92) { //Set RP Description
		// The Sui Box.
		ZoneServer* server = player->getZoneServer();
		ManagedReference<SuiInputBox*> ibox = new SuiInputBox(player, SuiWindowType::CITY_RENAME);
		ibox->setCallback(new SetDescriptionCallback(server, sceneObject));
		ibox->setUsingObject(sceneObject);
		ibox->setMaxInputSize(99999);
		ibox->setPromptTitle("Set Roleplay Description");
		ibox->setPromptText("Set the description that players will see when examining this object.");

		// Add to player.
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		ghost->addSuiBox(ibox);
		player->sendMessage(ibox->generateMessage());
	}

	if(selectedID == 93) { //Set Writeable

	} 

	if(selectedID == 94) { //Copy Object
		BorrieRPG::copyTarget(player, sceneObject, true);
	} 

	if(selectedID == 95) { //Rename Object
		// The Sui Box.
		ZoneServer* server = player->getZoneServer();
		ManagedReference<SuiInputBox*> ibox = new SuiInputBox(player, SuiWindowType::CITY_RENAME);
		ibox->setCallback(new SetNameCallback(server, sceneObject));
		ibox->setUsingObject(sceneObject);
		ibox->setMaxInputSize(99999);
		ibox->setPromptTitle("Set New Name");
		ibox->setPromptText("Set the name you'd like this object to have.");

		// Add to player.
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		ghost->addSuiBox(ibox);
		player->sendMessage(ibox->generateMessage());
	}

	if(selectedID == 96) { //Give to Target
		ManagedReference<SceneObject*> playerTarget = player->getZoneServer()->getObject(player->getTargetID());
		if(playerTarget != nullptr) {
			if(playerTarget->isCreatureObject()) {
				CreatureObject* targetCreature = playerTarget->asCreatureObject();
				ManagedReference<SceneObject*> inventory = playerTarget->getSlottedObject("inventory");
				if (inventory == nullptr || inventory->isContainerFullRecursive()) {
					player->sendSystemMessage("Target inventory is full, so the item could not be sent.");
					return 0;
				}

				if (inventory->transferObject(sceneObject, -1, true)) {
					inventory->broadcastObject(sceneObject, true);
					player->sendSystemMessage("Gave " + targetCreature->getCustomObjectName() + " \"" + sceneObject->getCustomObjectName() + ".\"" );
					targetCreature->sendSystemMessage("You recieved \"" + sceneObject->getCustomObjectName() + ".\"");
				} else {
					player->sendSystemMessage("Error transferring object to target.");
				}
			} else {
				player->sendSystemMessage("Your target needs to be a player.");
			}
		} else {
			player->sendSystemMessage("You need to have a target.");
		}
	}

	if(selectedID == 97) { //Set as mount
		sceneObject->setStoredInt("mount", 1);
	}
	
	return ObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);

}


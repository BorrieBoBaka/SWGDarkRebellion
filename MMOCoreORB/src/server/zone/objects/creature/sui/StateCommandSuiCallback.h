#ifndef STATECOMMANDSUICALLBACK_H_
#define STATECOMMANDSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class StateCommandSuiCallback : public SuiCallback {
private:
	int state;
	int pool;
	uint64 target;
	int adminLevel;

public:
	StateCommandSuiCallback(ZoneServer* server, uint64 _target, int _state, int _pool, int _adminLevel) : SuiCallback(server) {
		state = _state;
		pool = _pool;
		target = _target;
		adminLevel = _adminLevel;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed)
			return;

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

		if (playerManager == nullptr)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		ManagedReference<CreatureObject*> targetCreature;
		if (adminLevel > 0) {
			ManagedReference<SceneObject*> object;
			if (target != 0) {
				object = player->getZoneServer()->getObject(target, false);
			}

			if (object != nullptr) {
				if (object->isCreatureObject()) {
					targetCreature = object->asCreatureObject();
				} else {
					targetCreature = player;
				}
			} else {
				targetCreature = player;
			}

		} else {
			targetCreature = player;
		}

		if (state == 0) { // Initial Menu
			ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::JUKEBOX_SELECTION);

			if (adminLevel > 0) {
				box->setPromptTitle("HP Pool Menu, Target: " + targetCreature->getFirstName());
			} else {
				box->setPromptTitle("HP Pool Menu");
			}

			box->setCancelButton(true, "@cancel");

			if (index == -1)
				return;
			else if (index == 0) {
				// Add a State
				box->setCallback(new StateCommandSuiCallback(player->getZoneServer(), target, 1, 0, adminLevel));
				box->setPromptText("Select the state you wish to add.");
				box->addMenuItem("Set Stunned");
				box->addMenuItem("Set Blinded");
				box->addMenuItem("Set Immobilized");
				box->addMenuItem("Set Knocked Down");
				box->addMenuItem("Set On Fire");
				box->addMenuItem("Set Bleeding");
				

			} else if (index == 1) {
				// Remove a state
				box->setCallback(new StateCommandSuiCallback(player->getZoneServer(), target, 2, 0, adminLevel));
				box->setPromptText("Select the state you wish to clear.");
				box->addMenuItem("Remove Stunned");
				box->addMenuItem("Remove Blinded");
				box->addMenuItem("Remove Immobilized");
				box->addMenuItem("Remove On Fire");
				box->addMenuItem("Remove Bleeding");
			} else if (index == 2) {
				// Clear all States
				player->sendExecuteConsoleCommand("/rpaddstate clear");
				return;
			}

			player->getPlayerObject()->addSuiBox(box);
			player->sendMessage(box->generateMessage());

		} else if (state == 1 || state == 2) { // Select Pool to Mod
			if (state == 1) {
				if (index == 0) {
					player->sendExecuteConsoleCommand("/rpaddstate add stun");
				} else if (index == 1) {
					player->sendExecuteConsoleCommand("/rpaddstate add blind");
				} else if (index == 2) {
					player->sendExecuteConsoleCommand("/rpaddstate add immobilized");
				} else if (index == 3) {
					player->sendExecuteConsoleCommand("/rpaddstate add knockdown");
				} else if (index == 4) {
					player->sendExecuteConsoleCommand("/rpaddstate add fire");
				} else if (index == 5) {
					player->sendExecuteConsoleCommand("/rpaddstate add bleed");
				}

			} else {
				if (index == 0) {
					player->sendExecuteConsoleCommand("/rpaddstate remove stun");
				} else if (index == 1) {
					player->sendExecuteConsoleCommand("/rpaddstate remove blind");
				} else if (index == 2) {
					player->sendExecuteConsoleCommand("/rpaddstate remove immobilized");
				} else if (index == 3) {
					player->sendExecuteConsoleCommand("/rpaddstate remove fire");
				} else if (index == 4) {
					player->sendExecuteConsoleCommand("/rpaddstate remove bleed");
				}
			}

		} 
	}
};

#endif /* STATECOMMANDSUICALLBACK_H_ */

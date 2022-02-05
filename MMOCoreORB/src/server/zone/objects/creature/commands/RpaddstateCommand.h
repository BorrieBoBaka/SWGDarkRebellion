/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPADDSTATECOMMAND_H_
#define RPADDSTATECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

#include "server/zone/borrie/BorCharacter.h"

#include "server/zone/objects/creature/sui/StateCommandSuiCallback.h"

class RpaddstateCommand : public QueueCommand {

public: 
	RpaddstateCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		int adminLevelCheck = ghost->getAdminLevel();

		StringTokenizer args(arguments.toString());

		ManagedReference<SceneObject*> object;
		if (target != 0) {
			object = server->getZoneServer()->getObject(target, false);
		}

		ManagedReference<CreatureObject*> targetCreature;

		if (adminLevelCheck > 0) {
			if (object != nullptr) {
				if (object->isCreatureObject()) {
					targetCreature = object->asCreatureObject();
				} else {
					targetCreature = creature;
				}
			} else {
				targetCreature = creature;
			}
		} else {
			targetCreature = creature;
		}

		try {
			String command, subCommand;
			if (args.hasMoreTokens()) {
				args.getStringToken(command);
				// Direct Edit
				if (args.hasMoreTokens()) {
					args.getStringToken(subCommand);
					if (command == "add") {
						// Add state specified by subcommand
						BorCharacter::AddState(targetCreature, subCommand, true);
					} else if (command == "remove") {
						// Remove state specified by subcommand
						BorCharacter::RemoveState(targetCreature, subCommand, true);
					}
				} else {
					if (command == "reset" || command == "clear") {
						// Reset all States
						BorCharacter::ClearStates(targetCreature, true);
					} else {
						creature->sendSystemMessage("Invalid arguments for command. Try /rpaddstate <add/remove/reset> <stateName>");
					}
				}

			} else {
				// Open Menu, tell them who is the target. If I am at all privledged, make the target your target. Otherwise, target is yourself.
				ManagedReference<SuiListBox*> box = new SuiListBox(creature, SuiWindowType::JUKEBOX_SELECTION);
				box->setCallback(new StateCommandSuiCallback(creature->getZoneServer(), target, 0, 0, adminLevelCheck));
				if (adminLevelCheck > 0)
					box->setPromptTitle("State Menu, Target: " + targetCreature->getFirstName());
				else {
					box->setPromptTitle("State Menu");
				}
				box->setPromptText("Modify your States with the RP Add State command. Which action would you like to perform?");
				box->setCancelButton(true, "@cancel");
				box->addMenuItem("Add a State");
				box->addMenuItem("Remove a State");
				box->addMenuItem("Clear all States");
				creature->getPlayerObject()->addSuiBox(box);
				creature->sendMessage(box->generateMessage());
			}
		} catch (Exception& e) {
			creature->sendSystemMessage("Invalid arguments for rpaddstat command.");
		}
	
		return SUCCESS;
	}

};

#endif //RPADDSTATECOMMAND_H_
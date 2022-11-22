/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RESTRPCOMMAND_H_
#define RESTRPCOMMAND_H_

#include "server/zone/borrie/BorCharacter.h"
#include "server/zone/objects/creature/sui/RestRPCommandSuiCallback.h"

class RestRpCommand : public QueueCommand {
	

public:
	RestRpCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		int adminLevelCheck = ghost->getAdminLevel();

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

		StringTokenizer args(arguments.toString());

		if (args.hasMoreTokens()) {
			String command;
				args.getStringToken(command);
				if(command == "short") {
					BorCharacter::PerformShortRest(targetCreature);
				} else if(command == "long") {
					BorCharacter::FillAllPools(targetCreature);
				}
		} else {
			//Open SUI Menu
			//Pop up a Menu
				ManagedReference<SuiListBox*> box = new SuiListBox(creature, SuiWindowType::JUKEBOX_SELECTION);
				box->setCallback(new RestRPCommandSuiCallback(creature->getZoneServer(), target));
				box->setPromptTitle("Rest Menu");
				box->setPromptText("How long would you like to rest for? You can only take a long rest when in a safe location, outside of a mission.\n\nA short rest can be done anywhere outside of combat, but it will only restore your health pool by half of its value, and costs 2 will points.\n\nA long rest can be done only in a safe haven, but will completely rejuvinate all of your pools.");
				box->setCancelButton(true, "@cancel");
				box->addMenuItem("Short Rest");
				box->addMenuItem("Long Rest");
				creature->getPlayerObject()->addSuiBox(box);
				creature->sendMessage(box->generateMessage());
		}




		return SUCCESS;
	}

};

#endif 

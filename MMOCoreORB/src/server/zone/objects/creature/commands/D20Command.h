/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef D20COMMAND_H_
#define D20COMMAND_H_


#include "server/zone/borrie/BorrieRPG.h"
#include "server/zone/borrie/BorDice.h"
#include "server/zone/borrie/BorSkill.h"

#include "server/zone/objects/creature/sui/D20CommandSuiCallback.h"

class D20Command : public QueueCommand {

public:
	D20Command(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

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

		StringTokenizer args(arguments.toString());

		try {

			ManagedReference<SceneObject*> object;			  // The Target Object
			ManagedReference<CreatureObject*> targetCreature; // The Target Object as a Creature

			if (target != 0) {
				object = server->getZoneServer()->getObject(target, false);
				if (object->isCreatureObject())
					targetCreature = object->asCreatureObject();
				else
					targetCreature = creature;
			} else
				targetCreature = creature;

			String command, Result, secondCommand;
			if (args.hasMoreTokens()) {
				args.getStringToken(command);
				command = command.toLowerCase();

				

				if (command == "help") {
					HelpDisplay(creature);
				} else if (BorSkill::GetStringIsSkill(command)) {
					BorrieRPG::BroadcastRoll(creature, BorDice::RollSkill(creature, command));
				} else if (BorDice::GetCommandIsDie(command)) {
					if (args.hasMoreTokens()) {
						args.getStringToken(secondCommand);
						Result = BorDice::RollRPDie(creature, command, Integer::valueOf(secondCommand));
					} else
						Result = BorDice::RollRPDie(creature, command);
					if (Result == "fail") {
						creature->sendSystemMessage("ERROR: Attempted to roll die for " + command + " and failed.");
					} else
						BorrieRPG::BroadcastRoll(creature, Result);
				} else {
					throw Exception();
				}
			} else {
				//Open SUI Menu
				ManagedReference<SuiListBox*> box = new SuiListBox(creature, SuiWindowType::JUKEBOX_SELECTION);
				box->setCallback(new D20CommandSuiCallback(creature->getZoneServer(), target, 1, adminLevelCheck));
				if (adminLevelCheck > 0)
					box->setPromptTitle("D20 Dicebag Menu, Target: " + targetCreature->getFirstName());
				else {
					box->setPromptTitle("D20 Dicebag Menu");
				}
				box->setPromptText("What would you like to do? Rolling a die will allow you to choose the die type and how many die to roll.\nYou can use this command by typing (/d20 <count>d<die> <modifier>), i.e. /d20 1d20 5, /d20 2d6, or /d20 4d10 -2");
				box->setCancelButton(true, "@cancel");
				box->addMenuItem("Roll a Die");
				box->addMenuItem("Roll Attribute");
				box->addMenuItem("Roll Skill");
				creature->getPlayerObject()->addSuiBox(box);
				creature->sendMessage(box->generateMessage());
			}
		} catch (Exception& e) {
			creature->sendSystemMessage("Invalid arguments for D20 command. Help: /d20 help");
		}

		return SUCCESS;
	}

	void HelpDisplay(CreatureObject* creature) const {
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
		StringBuffer text;
		text << "-D20 COMMAND-------------------" << endl;

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::NONE);
		box->setPromptTitle("D20 COMMAND HELP");
		box->setPromptText(text.toString());
		ghost->addSuiBox(box);
		creature->sendMessage(box->generateMessage());
	}

};

#endif 

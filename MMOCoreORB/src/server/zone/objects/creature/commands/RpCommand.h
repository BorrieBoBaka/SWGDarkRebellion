/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RPCOMMAND_H_
#define RPCOMMAND_H_

#include "server/zone/borrie/BorrieRPG.h"
#include "server/zone/borrie/BorNPC.h"
#include "server/zone/borrie/BorEffect.h"

class RpCommand : public QueueCommand {

public:
	RpCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

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
			String command, subCommand;
			if (args.hasMoreTokens()) {
				args.getStringToken(command);
			}
			command = command.toLowerCase();
			ManagedReference<SceneObject*> object;
			if (target != 0) {
				object = server->getZoneServer()->getObject(target, false);
			}

			if (command == "help") {
				HelpDisplay(creature);
			} else if (command == "effect") {
				// Intentionally left blank?
			} else if (command == "copy") {
				BorrieRPG::copyTarget(creature, object);
			} else if (command == "who") {

			} else if (command == "mood") {
				if (args.hasMoreTokens()) {
					args.getStringToken(subCommand);
					creature->setMoodString(subCommand, true);
				} else {
					creature->sendSystemMessage("ERROR: Mood command requires that you specify an mood name.");
				}
			} else if (command == "combat" || command == "atk") {
				BorEffect::ForceIntoCombat(creature);
			} else if (command == "range") {
				creature->sendSystemMessage("[ >>" + String::valueOf(BorNPC::GetTargetDistance(creature, server->getZoneServer()->getObject(target, false))) + "<< ]");
			} else if (command == "target") {
				BorrieRPG::SaveTarget(creature, object);
			} else if (BorrieRPG::GetChatTypeID(command) != -1) {
				if (args.hasMoreTokens()) {
					String speech = arguments.toString().subString(1 + command.length(), arguments.toString().length());
					BorNPC::SpeakThroughNPC(creature, server->getZoneServer()->getObject(target, false), false, speech, BorrieRPG::GetChatTypeID(command));
				} else {
					creature->sendSystemMessage("Speech command requires you to say something!");
				}
			}
		} catch (Exception& e) {
			creature->sendSystemMessage("Invalid arguments for RP command. Help: /rp help");
		}

		return SUCCESS;
	}

	void HelpDisplay(CreatureObject* creature) const {
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
		StringBuffer text;
		text << "-RP COMMAND-------------------" << endl;

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, SuiWindowType::NONE);
		box->setPromptTitle("RP COMMAND HELP");
		box->setPromptText(text.toString());
		ghost->addSuiBox(box);
		creature->sendMessage(box->generateMessage());
	}

};

#endif 

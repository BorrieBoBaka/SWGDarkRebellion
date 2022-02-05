/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef TURNHELPCOMMAND_H_
#define TURNHELPCOMMAND_H_

#include "server/zone/objects/creature/sui/TurnHelpSuiCallback.h"

class TurnhelpCommand : public QueueCommand {

public: 
	TurnhelpCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		int adminLevelCheck = ghost->getAdminLevel();

		StringTokenizer args(arguments.toString());

		ManagedReference<SuiListBox*> box = new SuiListBox(creature, SuiWindowType::JUKEBOX_SELECTION);
		box->setCallback(new TurnHelpSuiCallback(creature->getZoneServer()));
		box->setPromptTitle("Turn Help Menu");
		box->setPromptText("This menu provides a codex for all the possible actions one can take during a turn, split between major actions and minor actions. During your turn, you can perform one major action and one minor action, or two minor actions.");
		box->setCancelButton(true, "@cancel");
		box->addMenuItem("= Major Actions =");
		box->addMenuItem("1. Attack");
		box->addMenuItem("2. Heal");
		box->addMenuItem("3. Skill Interact");
		box->addMenuItem("4. Enter Stealth");
		box->addMenuItem("= Minor Actions =");
		box->addMenuItem("1. Move");
		box->addMenuItem("2. Equip/Unequip Item");
		box->addMenuItem("3. Change Posture");
		box->addMenuItem("4. Simple Interact");
		box->addMenuItem("5. Use Force Power");
		box->addMenuItem("6. Throw Object");
		creature->getPlayerObject()->addSuiBox(box);
		creature->sendMessage(box->generateMessage());

		return SUCCESS;
	}

};

#endif //TURNHELPCOMMAND_H_
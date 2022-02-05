#ifndef TURNHELPSUICALLBACK_H_
#define TURNHELPSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class TurnHelpSuiCallback : public SuiCallback {
public:
	TurnHelpSuiCallback(ZoneServer* server) : SuiCallback(server) {

	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);
		int index = Integer::valueOf(args->get(0).toString());

		if (cancelPressed)
			return;

		ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::JUKEBOX_SELECTION);
		box->setCallback(new TurnHelpSuiCallback(player->getZoneServer()));
		box->setPromptTitle("Turn Help Menu");
		box->setPromptText(
			"This menu provides a codex for all the possible actions one can take during a turn, split between major actions and minor actions. During your "
			"turn, you can perform one major action and one minor action, or two minor actions.");
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


	}

	String GetIndexDescription(int index) {
	
		if (index == 0) { //Major Action
			return "Major Action";
		} else if (index == 1) { //Attack
			return "Attack";
		} else if (index == 2) { //Heal
			return "Heal";
		} else if (index == 3) { //Skill Interact
			return "Skill Interact";
		} else if (index == 4) { //Enter Stealth
			return "Enter Stealth";
		} else if (index == 5) { //Minor Action
			return "Minor Action";
		} else if (index == 6) { //Move
			return "Move";
		} else if (index == 7) { //Equip/Unequip Item
			return "Equip/Unequip Item";
		} else if (index == 8) { //Change Posture
			return "Change Posture";
		} else if (index == 9) { //Simple Interact
			return "Simple Interact";
		} else if (index == 10) { //Use Force Power
			return "Use Force Power";
		} else if (index == 11) { //Throw Object
			return "Throw Object";
		} 

		return "You managed to select an option that doesn't exist. Impressive.";
	}

};

#endif /* TURNHELPSUICALLBACK_H_ */
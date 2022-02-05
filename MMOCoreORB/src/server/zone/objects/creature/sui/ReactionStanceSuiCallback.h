#ifndef REACTIONSTANCESUICALLBACK_H_
#define REACTIONSTANCESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class ReactionStanceSuiCallback : public SuiCallback {
private:
	int state;
	int selection;

public:
	ReactionStanceSuiCallback(ZoneServer* server, int _state, int _selection) : SuiCallback(server) {
		state = _state;
		selection = _selection;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);
		int index = Integer::valueOf(args->get(0).toString());

		if (cancelPressed)
			return;

		ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::JUKEBOX_SELECTION);
		box->setCallback(new TurnHelpSuiCallback(player->getZoneServer()));
		box->setPromptTitle("Reaction Stance Menu");
		box->setPromptText("Select the reaction stance you'd like to take. A reaction stance determines how you'll respond when attacked. Most actions beyond \"None\" will cost action points to execute.");
		box->setCancelButton(true, "@cancel");
		box->addMenuItem("None");
		box->addMenuItem("Defend");
		box->addMenuItem("Parry");
		box->addMenuItem("Dodge");
		box->addMenuItem("Lightsaber Deflect");
		box->addMenuItem("Force Deflect");
		box->addMenuItem("Force Absorb");

	}

	String GetIndexDescription(int index) {
		if (index == 0) { // Major Action
			return "Major Action";
		} else if (index == 1) { // Attack
			return "Attack";
		} else if (index == 2) { // Heal
			return "Heal";
		} else if (index == 3) { // Skill Interact
			return "Skill Interact";
		} else if (index == 4) { // Enter Stealth
			return "Enter Stealth";
		} else if (index == 5) { // Minor Action
			return "Minor Action";
		} else if (index == 6) { // Move
			return "Move";
		} else if (index == 7) { // Equip/Unequip Item
			return "Equip/Unequip Item";
		} else if (index == 8) { // Change Posture
			return "Change Posture";
		} else if (index == 9) { // Simple Interact
			return "Simple Interact";
		} else if (index == 10) { // Use Force Power
			return "Use Force Power";
		} else if (index == 11) { // Throw Object
			return "Throw Object";
		}

		return "You managed to select an option that doesn't exist. Impressive.";
	}
};

#endif /* REACTIONSTANCESUICALLBACK_H_ */
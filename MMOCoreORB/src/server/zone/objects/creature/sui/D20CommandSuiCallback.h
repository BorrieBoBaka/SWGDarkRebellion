#ifndef D20COMMANDSUICALLBACK_H_
#define D20COMMANDSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/borrie/BorrieRPG.h"
#include "server/zone/borrie/BorDice.h"

class D20CommandSuiCallback : public SuiCallback {
private:
	int state;
	uint64 target;
	int adminLevel;
	int dieType;

public:
	D20CommandSuiCallback(ZoneServer* server, uint64 _target, int _state, int _adminLevel, int _dieType = 0) : SuiCallback(server) {
		state = _state;
		target = _target;
		adminLevel = _adminLevel;
		dieType = _dieType;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		//Assigning who the target will be when it comes to rolling these bones.
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

		ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::JUKEBOX_SELECTION);
		
		if (adminLevel > 0) {
			box->setPromptTitle("D20 Dicebag Menu, Target: " + targetCreature->getFirstName());
		} else {
			box->setPromptTitle("D20 Dicebag Menu");
		}
		
		box->setCancelButton(true, "@cancel");
		bool overrideSui = false;

		//Logic
		if (state == 0) {
			box->setCallback(new D20CommandSuiCallback(player->getZoneServer(), target, 1, adminLevel));
			box->setPromptText(
				"What would you like to do? Rolling a die will allow you to choose the die type and how many die to roll.\nYou can use this command by typing " 
				"(/d20 <count>d<die> <modifier>), i.e. /d20 1d20 5, /d20 2d6, or /d20 4d10 -2");
			// Roll a die
			// --Pick the die type
			// --Use Number Input to set the count
			box->addMenuItem("Roll a Die");
			// Roll an attribute
			// --Get all attributes, list them.
			// --On selection, roll that attribute.
			box->addMenuItem("Roll Attribute");
			// Roll a skill
			// --Identical functionality to Attribute.
			box->addMenuItem("Roll Skill");

			
		} else if (state == 1) {	//Top Level Menu		
			if (index == 0) { //Roll a die
				box->setCallback(new D20CommandSuiCallback(player->getZoneServer(), target, 2, adminLevel));
				box->setPromptText("Select which kind of die you would like to roll.");
				box->addMenuItem("D2");
				box->addMenuItem("D4");
				box->addMenuItem("D6");
				box->addMenuItem("D8");
				box->addMenuItem("D10");
				box->addMenuItem("D12");
				box->addMenuItem("D20");
				box->addMenuItem("D100");
			} else if (index == 1) { //Roll a Attribute
				box->setCallback(new D20CommandSuiCallback(player->getZoneServer(), target, 3, adminLevel));
				box->setPromptText("Select which attribute you'd like to roll for.");
				box->addMenuItem("Awareness");
				box->addMenuItem("Charisma");
				box->addMenuItem("Constitution");
				box->addMenuItem("Dexterity");
				box->addMenuItem("Intelligence");
				box->addMenuItem("Mindfulness");
				box->addMenuItem("Precision");
				box->addMenuItem("Strength");
			} else if (index == 2) { //Roll a skill
				box->setCallback(new D20CommandSuiCallback(player->getZoneServer(), target, 4, adminLevel));
				box->setPromptText("Select which skill you'd like to roll for.");
				box->addMenuItem("Armor");
				box->addMenuItem("Athletics");
				box->addMenuItem("Bluff");
				box->addMenuItem("Composure");
				box->addMenuItem("Computers");
				box->addMenuItem("Defending");
				box->addMenuItem("Demolitions");
				box->addMenuItem("Engineering");
				box->addMenuItem("Intimidation");
				box->addMenuItem("Investigation");
				box->addMenuItem("Larceny");
				box->addMenuItem("Maneuverability");
				box->addMenuItem("Mechanics");
				box->addMenuItem("Medicine");
				box->addMenuItem("Melee");
				box->addMenuItem("Persuasion");
				box->addMenuItem("Piloting");
				box->addMenuItem("Ranged");
				box->addMenuItem("Resolve");
				box->addMenuItem("Science");
				box->addMenuItem("Slicing");
				box->addMenuItem("Stealth");
				box->addMenuItem("Survival");
				box->addMenuItem("Throwing");
				box->addMenuItem("Unarmed");
				// Jedi
				if (player->getPlayerObject()->getJediState() > 0 || adminLevel > 0) {
					box->addMenuItem("Lightsaber");
					box->addMenuItem("Sense");
					box->addMenuItem("Lightning");
					box->addMenuItem("Telekinesis");
					box->addMenuItem("Control");
					box->addMenuItem("Alter");
					box->addMenuItem("Inward");
				}
			}
		} else if (state == 2) { //Die Menu
			overrideSui = true;
			ManagedReference<SuiInputBox*> hpModifyBox = new SuiInputBox(player, SuiWindowType::STRUCTURE_SET_ACCESS_FEE);
			hpModifyBox->setPromptTitle("D20 Dicebag Menu Die Input"); // Access Fee
			hpModifyBox->setCallback(new D20CommandSuiCallback(player->getZoneServer(), target, 5, adminLevel, index));
			hpModifyBox->setMaxInputSize(4);
			hpModifyBox->setPromptText("How many die would you like to roll? i.e. 2d20");
			player->getPlayerObject()->addSuiBox(hpModifyBox);
			player->sendMessage(hpModifyBox->generateMessage());
		} else if (state == 3) { //Roll Attribute
			//Gather which selected attribute via index.
			String attribute = GetAttributeStringFromID(index);
			BorrieRPG::BroadcastRoll(targetCreature, BorDice::RollSkill(targetCreature, attribute));
			return;
		} else if (state == 4) { //Roll Skill
			// Gather which selected skill via index.
			String skill = GetSkillStringFromID(index);
			BorrieRPG::BroadcastRoll(targetCreature, BorDice::RollSkill(targetCreature, skill));
			return;
		} else if (state == 5) { //Roll Die
			//Use die type and then the args to run the die.
			StringBuffer newCom;
			newCom << "/d20 " << args->get(0).toString() << "d" << GetDieType(dieType);
			player->sendExecuteConsoleCommand(newCom.toString());
			return;
		} 

		if (!overrideSui) {
			player->getPlayerObject()->addSuiBox(box);
			player->sendMessage(box->generateMessage());
		}
		
	}

	int GetDieType(int index) {
		if (index == 0) {
			return 2;
		} else if (index == 1) {
			return 4;
		} else if (index == 2) {
			return 6;
		} else if (index == 3) {
			return 8;
		} else if (index == 4) {
			return 10;
		} else if (index == 5) {
			return 12;
		} else if (index == 6) {
			return 20;
		} else if (index == 7) {
			return 100;
		} else
			return 999;
	} 

	String GetAttributeStringFromID(int id) {
		if (id == 0)
			return "awareness";
		else if (id == 1)
			return "charisma";
		else if (id == 2)
			return "constitution";
		else if (id == 3)
			return "dexterity";
		else if (id == 4)
			return "intelligence";
		else if (id == 5)
			return "mindfulness";
		else if (id == 6)
			return "precision";
		else if (id == 7)
			return "strength";
		else
			return "";
	}

	String GetSkillStringFromID(int id) {
		if (id == 0)
			return "armor";
		else if (id == 1)
			return "athletics";
		else if (id == 2)
			return "bluff";
		else if (id == 3)
			return "composure";
		else if (id == 4)
			return "computers";
		else if (id == 5)
			return "defending";
		else if (id == 6)
			return "demolitions";
		else if (id == 7)
			return "engineering";
		else if (id == 8)
			return "intimidation";
		else if (id == 9)
			return "investigation";
		else if (id == 10)
			return "larceny";
		else if (id == 11)
			return "maneuverability";
		else if (id == 12)
			return "mechanics";
		else if (id == 13)
			return "medicine";
		else if (id == 14)
			return "melee";
		else if (id == 15)
			return "persuasion";
		else if (id == 16)
			return "piloting";
		else if (id == 17)
			return "ranged";
		else if (id == 18)
			return "resolve";
		else if (id == 19)
			return "science";
		else if (id == 20)
			return "slicing";
		else if (id == 21)
			return "stealth";
		else if (id == 22)
			return "survival";
		else if (id == 23)
			return "throwing";
		else if (id == 24)
			return "unarmed";
		else if (id == 25)
			return "lightsaber";
		else if (id == 26)
			return "sense";
		else if (id == 27)
			return "lightning";
		else if (id == 28)
			return "telekinesis";
		else if (id == 29)
			return "control";
		else if (id == 30)
			return "alter";
		else if (id == 31)
			return "inward";
		else
			return "";
	}
};

#endif
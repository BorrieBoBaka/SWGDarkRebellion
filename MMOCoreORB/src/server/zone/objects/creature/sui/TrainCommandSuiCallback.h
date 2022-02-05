#ifndef TRAINCOMMANDSUICALLBACK_H_
#define TRAINCOMMANDSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class TrainCommandSuiCallback : public SuiCallback {
private:
	int state;
	int selection;

public:
	TrainCommandSuiCallback(ZoneServer* server, int _state, int _selection) : SuiCallback(server) {
		state = _state;
		selection = _selection;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

		if (playerManager == nullptr)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());


		if (state == -1) {//Top Menu
			ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::JUKEBOX_SELECTION);
			box->setCallback(new TrainCommandSuiCallback(server, 0, 0));
			box->setPromptTitle("Training Menu");
			box->setPromptText("What would you like to do?");
			box->setCancelButton(true, "@cancel");
			//box->setOkButton(false, "@");
			box->addMenuItem("Train an Attribute");
			box->addMenuItem("Train a Skill");
			box->addMenuItem("Convert General Roleplay XP");
			player->getPlayerObject()->addSuiBox(box);
			player->sendMessage(box->generateMessage());
		} else if (state == 0) { //Primary Menu		
			if (cancelPressed)
				return;

			if (index == 0 || index == 1) {		
				ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::JUKEBOX_SELECTION);
				box->setCancelButton(true, "Back");
				//box->setOkButton(false, "@");
				if (index == 0) { // Train Attribute
					box->setCallback(new TrainCommandSuiCallback(server, 1, index));
					box->setPromptTitle("Training Attribute Menu");
					box->setPromptText("What attribute would you like to rank up?");
					box->addMenuItem("Awareness " + String::valueOf(player->getSkillMod("rp_awareness")));
					box->addMenuItem("Charisma " + String::valueOf(player->getSkillMod("rp_charisma")));
					box->addMenuItem("Constitution " + String::valueOf(player->getSkillMod("rp_constitution")));
					box->addMenuItem("Dexterity " + String::valueOf(player->getSkillMod("rp_dexterity")));
					box->addMenuItem("Intelligence " + String::valueOf(player->getSkillMod("rp_intelligence")));
					box->addMenuItem("Mindfulness " + String::valueOf(player->getSkillMod("rp_mindfulness")));
					box->addMenuItem("Precision " + String::valueOf(player->getSkillMod("rp_precision")));
					box->addMenuItem("Strength " + String::valueOf(player->getSkillMod("rp_strength")));
				} else if (index == 1) { // Train Skill
					box->setCallback(new TrainCommandSuiCallback(server, 2, index));
					box->setPromptTitle("Training Skill Menu");
					box->setPromptText("What skill would you like to rank up? Remember that skills can only go as high as their associated attribute's max rank.");
					box->addMenuItem("Armor " +				String::valueOf(player->getSkillMod("rp_armor")));
					box->addMenuItem("Athletics " +			String::valueOf(player->getSkillMod("rp_athletics")));
					box->addMenuItem("Bluff " +				String::valueOf(player->getSkillMod("rp_bluff")));
					box->addMenuItem("Composure " +			String::valueOf(player->getSkillMod("rp_composure")));
					box->addMenuItem("Computers " +			String::valueOf(player->getSkillMod("rp_computers")));
					box->addMenuItem("Defending " +			String::valueOf(player->getSkillMod("rp_defending")));
					box->addMenuItem("Demolitions " +		String::valueOf(player->getSkillMod("rp_demolitions")));
					box->addMenuItem("Engineering " +		String::valueOf(player->getSkillMod("rp_engineering")));
					box->addMenuItem("Intimidation " +		String::valueOf(player->getSkillMod("rp_intimidation")));
					box->addMenuItem("Investigation " +		String::valueOf(player->getSkillMod("rp_investigation")));
					box->addMenuItem("Larceny " +			String::valueOf(player->getSkillMod("rp_larceny")));
					box->addMenuItem("Maneuverability " +	String::valueOf(player->getSkillMod("rp_maneuverability")));
					box->addMenuItem("Mechanics " +			String::valueOf(player->getSkillMod("rp_mechanics")));
					box->addMenuItem("Medicine " +			String::valueOf(player->getSkillMod("rp_medicine")));
					box->addMenuItem("Melee " +				String::valueOf(player->getSkillMod("rp_melee")));
					box->addMenuItem("Persuasion " +		String::valueOf(player->getSkillMod("rp_persuasion")));
					box->addMenuItem("Piloting " +			String::valueOf(player->getSkillMod("rp_piloting")));
					box->addMenuItem("Ranged " +			String::valueOf(player->getSkillMod("rp_ranged")));
					box->addMenuItem("Resolve " +			String::valueOf(player->getSkillMod("rp_resolve")));
					box->addMenuItem("Science " +			String::valueOf(player->getSkillMod("rp_science")));
					box->addMenuItem("Slicing " +			String::valueOf(player->getSkillMod("rp_slicing")));
					box->addMenuItem("Stealth " +			String::valueOf(player->getSkillMod("rp_stealth")));
					box->addMenuItem("Survival " +			String::valueOf(player->getSkillMod("rp_survival")));
					box->addMenuItem("Throwing " +			String::valueOf(player->getSkillMod("rp_throwing")));
					box->addMenuItem("Unarmed " +			String::valueOf(player->getSkillMod("rp_unarmed")));
					//Jedi
					if (player->getPlayerObject()->getJediState() > 0) {
						box->addMenuItem("Lightsaber " + String::valueOf(player->getSkillMod("rp_lightsaber")));
						box->addMenuItem("Sense " + String::valueOf(player->getSkillMod("rp_sense")));
						box->addMenuItem("Lightning " + String::valueOf(player->getSkillMod("rp_lightning")));
						box->addMenuItem("Telekinesis " + String::valueOf(player->getSkillMod("rp_telekinesis")));
						box->addMenuItem("Control " + String::valueOf(player->getSkillMod("rp_control")));
						box->addMenuItem("Alter " + String::valueOf(player->getSkillMod("rp_alter")));
						box->addMenuItem("Inward " + String::valueOf(player->getSkillMod("rp_inward")));
					}
				}
				player->getPlayerObject()->addSuiBox(box);
				player->sendMessage(box->generateMessage());
			} else if (index == 2) { //Convert Exp

			}
		} else if (state == 1) { //Select Attribute
			//Get index as skill
			String skillName = GetAttributeStringFromID(index);
			//Check to see what the next level of that skill is
			//See if they quality for that skill
			int currentRank = player->getSkillMod("rp_" + skillName);
			// Give them a new SUI box option either confirming, or informing that they can't train that right now. 
			ManagedReference<SuiMessageBox*> suibox = new SuiMessageBox(player, SuiWindowType::TEACH_OFFER);
			if (CanTrainNextSkill(player, currentRank + 1, skillName)) {
				suibox->setPromptTitle("Confirm training?"); 
				//Can train!
				suibox->setPromptText("Are you sure you want to train this attribute?");
				suibox->setCallback(new TrainCommandSuiCallback(server, 3, index));
				suibox->setOkButton(true, "Confirm");
				suibox->setCancelButton(true, "Go Back");
			} else {
				suibox->setPromptTitle("Not eligible for training.");
				//Failure. Can't train.
				suibox->setPromptText("You are not currently eligible to train this attribute. You do not have enough experience points.");
				//suibox->setCallback(new PlayerTeachConfirmSuiCallback(server, skill));
				suibox->setCallback(new TrainCommandSuiCallback(server, -1, state));
				suibox->setCancelButton(true, "Go Back");
			}	
			player->getPlayerObject()->addSuiBox(suibox);
			player->sendMessage(suibox->generateMessage());
		} else if (state == 2) { //Select Skill
		
		} else if (state == 3) { //Train a Attribute
			String skill = GetAttributeStringFromID(selection);
			int currentRank = player->getSkillMod("rp_" + skill);
			if (CanTrainNextSkill(player, currentRank + 1, skill)) {
				//Train it
				SkillManager* skillManager = SkillManager::instance();
				skillManager->awardSkill("rp_" + skill + "_" + GetSkillSuffixFromValue(currentRank + 1), player, true, false, false);
			} else {
				//Something happened
				player->sendSystemMessage("ERROR: Something happened. You were eligible for the skill you selected when you selected it, but you are no longer eligible.");
			}
			
		} else if (state == 4) { //Train a Skill
		
		} else if (state == 5) { //Convert Exp
		
		}
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
			return "engineering";
		else if (id == 9)
			return "intimidation";
		else if (id == 10)
			return "investigation";
		else if (id == 11)
			return "larceny";
		else if (id == 12)
			return "maneuverability";
		else if (id == 13)
			return "mechanics";
		else if (id == 14)
			return "medicine";
		else if (id == 15)
			return "melee";
		else if (id == 16)
			return "persuasion";
		else if (id == 17)
			return "piloting";
		else if (id == 18)
			return "ranged";
		else if (id == 19)
			return "resolve";
		else if (id == 20)
			return "science";
		else if (id == 21)
			return "slicing";
		else if (id == 22)
			return "stealth";
		else if (id == 23)
			return "survival";
		else if (id == 24)
			return "throwing";
		else if (id == 25)
			return "unarmed";
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

	String GetSkillSuffixFromValue(int value) {
		if (value == 1)
			return "novice";
		else if (value == 2)
			return "a01";
		else if (value == 3)
			return "a02";
		else if (value == 4)
			return "a03";
		else if (value == 5)
			return "a04";
		else if (value == 6)
			return "b01";
		else if (value == 7)
			return "b02";
		else if (value == 8)
			return "b03";
		else if (value == 9)
			return "b04";
		else if (value == 10)
			return "master";
		else
			return "novice";
	}

	bool CanTrainNextSkill(CreatureObject* creature, int rank, String skill, String parentAttribute = "") {
		String skillName = "rp_" + skill + "_" + GetSkillSuffixFromValue(rank);
		SkillManager* skillManager = SkillManager::instance();
		bool hasXP = skillManager->canLearnSkill(skillName, creature, false);
		if (parentAttribute != "") {
			int parentValue = creature->getSkillMod("rp_" + parentAttribute);
			if (parentValue < rank)
				return false;
		}

		return hasXP;
	}

	String GetSkillParent(String skill) {
		if (skill == "melee")
			return "strength";
		else if (skill == "intimidation")
			return "strength";
		else if (skill == "unarmed")
			return "strength";
		else if (skill == "lightsaber")
			return "strength";
		else if (skill == "ranged")
			return "precision";
		else if (skill == "mechanics")
			return "precision";
		else if (skill == "demolitions")
			return "precision";
		else if (skill == "engineering")
			return "precision";
		else if (skill == "larceny")
			return "dexterity";
		else if (skill == "stealth")
			return "dexterity";
		else if (skill == "maneuverability")
			return "dexterity";
		else if (skill == "throwing")
			return "dexterity";
		else if (skill == "investigation")
			return "awareness";
		else if (skill == "piloting")
			return "awareness";
		else if (skill == "survival")
			return "awareness";
		else if (skill == "sense")
			return "awareness";
		else if (skill == "slicing")
			return "intelligence";
		else if (skill == "computers")
			return "intelligence";
		else if (skill == "medicine")
			return "intelligence";
		else if (skill == "science")
			return "intelligence";
		else if (skill == "persuasion")
			return "charisma";
		else if (skill == "bluff")
			return "charisma";
		else if (skill == "composure")
			return "charisma";
		else if (skill == "resolve")
			return "charisma";
		else if (skill == "athletics")
			return "constitution";
		else if (skill == "lightning")
			return "constitution";
		else if (skill == "armor")
			return "constitution";
		else if (skill == "defending")
			return "constitution";
		else if (skill == "telekinesis")
			return "mindfulness";
		else if (skill == "control")
			return "mindfulness";
		else if (skill == "alter")
			return "mindfulness";
		else if (skill == "inward")
			return "mindfulness";
		else
			return "";
	}

};

#endif /* TRAINCOMMANDSUICALLBACK_H_ */
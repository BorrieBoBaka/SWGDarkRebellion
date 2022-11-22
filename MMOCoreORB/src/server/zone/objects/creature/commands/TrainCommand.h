/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TRAINCOMMAND_H_
#define TRAINCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

#include "server/zone/borrie/BorCharacter.h"

#include "server/zone/objects/creature/sui/TrainCommandSuiCallback.h"

class TrainCommand : public QueueCommand {

public:
	TrainCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		int adminLevelCheck = ghost->getAdminLevel();

		StringTokenizer args(arguments.toString());


		try {
			int freeSkillPoints = creature->getStoredInt("starter_skill_points");
			int freeAttrPoints = creature->getStoredInt("starter_attr_points");
			ManagedReference<SuiListBox*> box = new SuiListBox(creature, SuiWindowType::JUKEBOX_SELECTION);
			box->setCallback(new TrainCommandSuiCallback(creature->getZoneServer(), 0, 0));
			box->setPromptTitle("Training Menu");
			if(freeSkillPoints > 0 || freeAttrPoints > 0) {
				box->setPromptText("What would you like to do?\n\nFree Attribute Boxes: " + String::valueOf(freeAttrPoints) + "\nFree Skill Boxes: " + String::valueOf(freeSkillPoints));
			} else box->setPromptText("What would you like to do?");			
			box->setCancelButton(true, "@cancel");
			box->setOkButton(false, "@");
			box->addMenuItem("Train an Attribute");
			box->addMenuItem("Train a Skill");
			//box->addMenuItem("Convert General Roleplay XP");
			creature->getPlayerObject()->addSuiBox(box);
			creature->sendMessage(box->generateMessage());
		} catch (Exception& e) {
			creature->sendSystemMessage("Error encountered when using train command.");
		}
		return SUCCESS;
	}

};

#endif 

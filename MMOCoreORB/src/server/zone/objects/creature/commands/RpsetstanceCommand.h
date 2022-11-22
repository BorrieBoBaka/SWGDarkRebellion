/*
				Copyright <SWGEmu>
			Command written by Borrie BoBaka
		See file COPYING for copying conditions.*/

#ifndef RPSETSTANCECOMMAND_H_
#define RPSETSTANCECOMMAND_H_

#include "server/zone/objects/creature/sui/ReactionStanceSuiCallback.h"

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

#include "server/zone/borrie/BorCharacter.h"

class RpsetstanceCommand : public QueueCommand {
public:
	RpsetstanceCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
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

		ManagedReference<CreatureObject*> targetCreature;

		ManagedReference<SceneObject*> object;
		if (target != 0) {
			object = server->getZoneServer()->getObject(target, false);
		}

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
			String command, selectionName = "";
			if (args.hasMoreTokens()) {
				args.getStringToken(command);

				if(command == "none" || command == "clear") {
					targetCreature->setStoredInt("reaction_stance", 0);
					selectionName = "No Action";
				} else if(command == "defend" || command == "defense") {
					targetCreature->setStoredInt("reaction_stance", 1);
					selectionName = "Defend";
				} else if(command == "parry") {
					targetCreature->setStoredInt("reaction_stance", 2);
					selectionName = "Parry";
				} else if(command == "dodge") {
					targetCreature->setStoredInt("reaction_stance", 3);
					selectionName = "Dodge";
				} else if(command == "deflect" || command == "lsdeflect") {
					if(targetCreature->getSkillMod("rp_lightsaber") > 0) {
						targetCreature->setStoredInt("reaction_stance", 4);
						selectionName = "Deflect";
					} else {
						creature->sendSystemMessage("You can't use that stance.");
						return GENERALERROR;
					}					
				} else if(command == "fdeflect" || command == "forcedeflect") {
					if(targetCreature->getSkillMod("rp_telekinesis") > 0) {
						targetCreature->setStoredInt("reaction_stance", 5);
						selectionName = "Force Deflect";
					} else {
						creature->sendSystemMessage("You can't use that stance.");
						return GENERALERROR;
					}					
				} else if(command == "absorb" || command == "forceabsorb") {
					if(targetCreature->getSkillMod("rp_inward") > 0)  {
						targetCreature->setStoredInt("reaction_stance", 6);
						selectionName = "Force Absorb";
					} else {
						creature->sendSystemMessage("You can't use that stance.");
						return GENERALERROR;
					}					
				} else {
					creature->sendSystemMessage("That is not a valid combat stance. Valid stances are: 'none', 'parry', 'dodge', 'deflect', 'forcedeflect', and 'absorb'.");
				}

				if(selectionName != "") {
					if(targetCreature == creature) creature->sendSystemMessage("You've set your combat reaction stance to: " + selectionName);
					else creature->sendSystemMessage("You've set "+targetCreature->getFirstName()+"'s combat reaction stance to: " + selectionName);
				}
			} else {
				//Pop up a Menu
				ManagedReference<SuiListBox*> box = new SuiListBox(creature, SuiWindowType::JUKEBOX_SELECTION);
				box->setCallback(new ReactionStanceSuiCallback(creature->getZoneServer(), 0, 0));
				box->setPromptTitle("Reaction Stance Menu");
				box->setPromptText("Select the reaction stance you'd like to take. A reaction stance determines how you'll respond when attacked. Most actions beyond \"None\" will cost action points to execute.");
				box->setCancelButton(true, "@cancel");
				box->addMenuItem("None");
				box->addMenuItem("Defend");
				box->addMenuItem("Parry");
				box->addMenuItem("Dodge");
				if(targetCreature->getSkillMod("rp_lightsaber")) box->addMenuItem("Lightsaber Deflect");
				if(targetCreature->getSkillMod("rp_telekinesis")) box->addMenuItem("Force Deflect");
				if(targetCreature->getSkillMod("rp_inward")) box->addMenuItem("Force Absorb");
				creature->getPlayerObject()->addSuiBox(box);
				creature->sendMessage(box->generateMessage());
			}


		} catch (Exception& e) {
			creature->sendSystemMessage("Invalid arguments for RpSetStanceCommand command.");
		}


		return SUCCESS;
	}
};

#endif // RPSETSTANCECOMMAND_H_
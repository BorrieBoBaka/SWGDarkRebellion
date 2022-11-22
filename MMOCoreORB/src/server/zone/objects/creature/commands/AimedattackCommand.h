/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef AIMEDATTACKCOMMAND_H_
#define AIMEDATTACKCOMMAND_H_

#include "server/zone/objects/creature/sui/AimedAttackCommandSuiCallback.h"

class AimedattackCommand : public QueueCommand {

public: 
	AimedattackCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
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

		if (creature->getStoredInt("secretdm") == 1) {
			adminLevelCheck = 15;
		}

		ManagedReference<SceneObject*> object;
		if (target != 0) {
			object = server->getZoneServer()->getObject(target, false);
		} else {
			creature->sendSystemMessage("You need a target to attack!");
			return SUCCESS;
		}

		ManagedReference<CreatureObject*> targetCreature;

		if (object->isCreatureObject()) {
			targetCreature = object->asCreatureObject();
		} else {
			creature->sendSystemMessage("You need a target to attack!");
			return SUCCESS;
		}

		StringTokenizer args(arguments.toString());

		String command; 

		if (args.hasMoreTokens()) {
			args.getStringToken(command);
			if(command == "legs" || command == "leg" || command == "knee" || command == "knees" || command == "dick" || command == "crotch" || command == "shins" || command == "groin") {
				BorCombat::AttackTarget(creature, targetCreature, creature, 3, false);
			} else if(command == "forearm" || command == "lowerarm" || command == "bracer") {
				if(command == "left") {
					BorCombat::AttackTarget(creature, targetCreature, creature, 5, false);
				} else {
					BorCombat::AttackTarget(creature, targetCreature, creature, 6, false);
				}
			} else if(command == "bicep" || command == "upperarm" || command == "shoulder") {
				if(command == "left") {
					BorCombat::AttackTarget(creature, targetCreature, creature, 7, false);
				} else {
					BorCombat::AttackTarget(creature, targetCreature, creature, 8, false);
				}
			} else if(command == "feet" || command == "foot" || command == "toes"  || command == "hoof" || command == "paw") {
				BorCombat::AttackTarget(creature, targetCreature, creature, 4, false);
			} else if(command == "chest" || command == "heart"  || command == "stomach" || command == "gut" || command == "ribs") {
				BorCombat::AttackTarget(creature, targetCreature, creature, 1, false);
			} else if(command == "hands"  || command == "gloves" || command == "fingers") {
				BorCombat::AttackTarget(creature, targetCreature, creature, 9, false);
			} else if (command == "head" || command == "face" || command == "eyes" || command == "neck" || command == "hat" || command == "helmet") {
				BorCombat::AttackTarget(creature, targetCreature, creature, 10, false);
			} else {
				//Open SUI
				OpenSUI(creature, targetCreature);
			}
		} else {
			//Open SUI
			OpenSUI(creature, targetCreature);
		}


		return SUCCESS;
	}

	void OpenSUI(CreatureObject* creature, CreatureObject* targetCreature) const {
		try {
			ManagedReference<SuiListBox*> box = new SuiListBox(creature, SuiWindowType::JUKEBOX_SELECTION);
			box->setCallback(new AimedAttackCommandSuiCallback(creature->getZoneServer(), 0, 0, targetCreature));
			box->setPromptTitle("Aimed Attack Menu");
			box->setCancelButton(true, "@cancel");
			box->setOkButton(false, "@");
			box->addMenuItem("Chest");
			box->addMenuItem("Legs");
			box->addMenuItem("Feet");
			box->addMenuItem("Left Forearm");
			box->addMenuItem("Right Forearm");
			box->addMenuItem("Left Bicep");
			box->addMenuItem("Right Bicep");
			box->addMenuItem("Hands");
			box->addMenuItem("Head");
			creature->getPlayerObject()->addSuiBox(box);
			creature->sendMessage(box->generateMessage());
		} catch (Exception& e) {
			creature->sendSystemMessage("Error encountered when using train command.");
		}
	}

};

#endif //AIMEDATTACKCOMMAND_H_
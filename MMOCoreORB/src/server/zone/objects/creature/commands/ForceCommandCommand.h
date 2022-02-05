/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCECOMMANDCOMMAND_H_
#define FORCECOMMANDCOMMAND_H_

#include "server/zone/borrie/BorDev.h"

class ForceCommandCommand : public QueueCommand {
public:

	ForceCommandCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
		ManagedReference<SceneObject*> object;
		ManagedReference<CreatureObject*> creo;
		StringTokenizer args(arguments.toString());

		if (target != 0) {
			object = server->getZoneServer()->getObject(target, false);
		}

		String command, subCommand, subSubCommand;
		if (args.hasMoreTokens()) {
			args.getStringToken(command);
		}

		command = command.toLowerCase();

		if (command == "test") {
			BorDev::SendHelloWorld(creature);
		} else if (command == "combat") {
			if (object != nullptr) {
				if (object->isCreatureObject()) {
					BorDev::ToggleCombat(object->asCreatureObject());
				} else {
					BorDev::ToggleCombat(creature);
				}
			} else {
				BorDev::ToggleCombat(creature);
			}
			
		} else if (command == "goto") {
			BorDev::creatureGoto(creature, target);
		} else if (command == "follow") {
			BorDev::creatureFollow(creature, target);
		} else if (command == "stay") {
			BorDev::creatureStay(creature, target);
		} else if (command == "ai") {
			if (object->isCreatureObject()) {
				BorDev::ToggleAlwaysOnAI(object->asCreatureObject(), creature);
			}
		} else if (command == "dirfol") {
			if (object->isCreatureObject()) {
				BorDev::ToggleDirectFollow(object->asCreatureObject(), creature);
			}
		} else if (command == "walk") {
			if (object->isCreatureObject()) {
				BorDev::ToggleAIWalks(object->asCreatureObject(), creature);
			}
		} else if (command == "fc") {
			if (object->isCreatureObject()) {
				BorDev::ToggleForceAICombat(object->asCreatureObject(), creature);
			}
		} else if (command == "client") {
			BorDev::SetCreatureClient(creature, target);
		} else if (command == "peace") {
			if (object != nullptr) {
				if (object->isCreatureObject()) {
					BorDev::StopCombat(object->asCreatureObject());
				} else {
					BorDev::StopCombat(creature);
				}
			} else {
				BorDev::StopCombat(creature);
			}
		} else if (command == "move") {
			BorDev::SetPosition(creature, target);
		} else if (command == "weaponm") {
			if (object != nullptr) {
				if (object->isCreatureObject()) {
					BorDev::EquipNPCWeapon(object->asCreatureObject(), false);
				}
			}			
		} else if (command == "weaponr") {
			if (object != nullptr) {
				if (object->isCreatureObject()) {
					BorDev::EquipNPCWeapon(object->asCreatureObject(), true);
				}
			}
		} else if (command == "posture0") {
			if (object->isCreatureObject()) {
				BorDev::SetNPCPosture(object->asCreatureObject(), 0);
			}
		} else if (command == "posture1") {
			if (object->isCreatureObject()) {
				BorDev::SetNPCPosture(object->asCreatureObject(), 1);
			}
		} else if (command == "posture2") {
			if (object->isCreatureObject()) {
				BorDev::SetNPCPosture(object->asCreatureObject(), 2);
			}
		} else if (command == "posture3") {
			if (object->isCreatureObject()) {
				BorDev::SetNPCPosture(object->asCreatureObject(), 3);
			}
		} else if (command == "posture4") {
			if (object->isCreatureObject()) {
				BorDev::SetNPCPosture(object->asCreatureObject(), 4);
			}
		} else if (command == "posture5") {
			if (object->isCreatureObject()) {
				BorDev::SetNPCPosture(object->asCreatureObject(), 5);
			}
		} else if (command == "posture6") {
			if (object->isCreatureObject()) {
				BorDev::SetNPCPosture(object->asCreatureObject(), 6);
			}
		} else if (command == "posture7") {
			if (object->isCreatureObject()) {
				BorDev::SetNPCPosture(object->asCreatureObject(), 7);
			}
		} else if (command == "posture8") {
			if (object->isCreatureObject()) {
				BorDev::SetNPCPosture(object->asCreatureObject(), 8);
			}
		} else if (command == "setheight") {
			if (object->isCreatureObject()) {
				if ((args.hasMoreTokens())) {
					float height = args.getFloatToken();
					Locker lclock(object->asCreatureObject());
					object->asCreatureObject()->setHeight(height, true);
				}
			}
			
		}

		

		return SUCCESS;
	}

};

#endif //FORCECOMMANDCOMMAND_H_

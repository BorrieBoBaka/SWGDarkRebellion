/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ENDTURNCOMMAND_H_
#define ENDTURNCOMMAND_H_

#include "server/zone/borrie/BorCharacter.h"

class EndTurnCommand : public QueueCommand {

public:
	EndTurnCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

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

		ManagedReference<SceneObject*> object;
		if (target != 0) {
			object = server->getZoneServer()->getObject(target, false);
		}

		ManagedReference<CreatureObject*> targetCreature;

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

		//Inform the turn has ended
		//Apply state rules. 
		BorCharacter::RemoveAllStates(targetCreature, false);

		BorrieRPG::BroadcastMessage(targetCreature, "[[" + targetCreature->getFirstName() + " has ended their turn!]]");
		BorCharacter::ApplyEndTurnStateDamages(targetCreature);

		return SUCCESS;
	}

};

#endif 

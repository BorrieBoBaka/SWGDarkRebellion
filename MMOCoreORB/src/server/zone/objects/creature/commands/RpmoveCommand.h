/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPMOVECOMMAND_H_
#define RPMOVECOMMAND_H_

#include "server/zone/borrie/BorCharacter.h"

class RpmoveCommand : public QueueCommand {
public:
	RpmoveCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
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

		try {
			bool isMoving = creature->getStoredInt("rp_moving") == 1;
			if (isMoving) {
				//Confirm
				BorCharacter::ConfirmRoleplayMove(creature);
				creature->deleteStoredInt("rp_moving");
			} else {
				//Initialize
				BorCharacter::InitializeRoleplayMove(creature);
				creature->setStoredInt("rp_moving", 1);
			}
		} catch (Exception& e) {
			creature->sendSystemMessage("Something went wrong.");
		}

		return SUCCESS;
	}
};

#endif // RPMOVECOMMAND_H_
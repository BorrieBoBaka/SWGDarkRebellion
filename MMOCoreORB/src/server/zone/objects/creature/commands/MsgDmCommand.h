/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MSGDMCOMMAND_H_
#define MSGDMCOMMAND_H_

#include "server/zone/borrie/BorrieRPG.h"

class MsgDmCommand : public QueueCommand {

public:
	MsgDmCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

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

		String command;
		if (args.hasMoreTokens()) {
			BorrieRPG::BroadcastToAdmins(creature, command);
		} else {
			creature->sendSystemMessage("Syntax: /msgdm <msg>");
			return GENERALERROR;
		}

		return SUCCESS;
	}

};

#endif 

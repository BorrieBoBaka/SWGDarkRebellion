/*
				Copyright <SWGEmu>
			Command written by Borrie BoBaka
		See file COPYING for copying conditions.*/

#ifndef RPSETSTANCECOMMAND_H_
#define RPSETSTANCECOMMAND_H_

#include "server/zone/objects/creature/sui/ReactionStanceSuiCallback.h"

class RpsetstanceCommand : public QueueCommand {
public:
	RpsetstanceCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		return SUCCESS;
	}
};

#endif // RPSETSTANCECOMMAND_H_
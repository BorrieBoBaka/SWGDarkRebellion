/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ATTACKRPCOMMAND_H_
#define ATTACKRPCOMMAND_H_

class AttackRpCommand : public QueueCommand {

public:
	AttackRpCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		return SUCCESS;
	}
};

#endif 

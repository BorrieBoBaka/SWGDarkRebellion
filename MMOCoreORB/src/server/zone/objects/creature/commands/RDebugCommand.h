/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RDEBUGCOMMAND_H_
#define RDEBUGCOMMAND_H_

class RDebugCommand : public QueueCommand {

public:
	RDebugCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		return SUCCESS;
	}

};

#endif 

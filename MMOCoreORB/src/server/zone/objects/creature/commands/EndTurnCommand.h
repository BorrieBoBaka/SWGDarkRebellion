/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ENDTURNCOMMAND_H_
#define ENDTURNCOMMAND_H_

class EndTurnCommand : public QueueCommand {

public:
	EndTurnCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		return SUCCESS;
	}

};

#endif 

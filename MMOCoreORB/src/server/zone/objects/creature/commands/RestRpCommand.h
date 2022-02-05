/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RESTRPCOMMAND_H_
#define RESTRPCOMMAND_H_

class RestRpCommand : public QueueCommand {

public:
	RestRpCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		return SUCCESS;
	}

};

#endif 

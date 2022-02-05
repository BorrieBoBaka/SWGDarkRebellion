/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef POWERATTACKCOMMAND_H_
#define POWERATTACKCOMMAND_H_

class PowerattackCommand : public QueueCommand {

public: 
	PowerattackCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //POWERATTACKCOMMAND_H_
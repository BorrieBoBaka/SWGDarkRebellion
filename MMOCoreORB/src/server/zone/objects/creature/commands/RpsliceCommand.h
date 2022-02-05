/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPSLICECOMMAND_H_
#define RPSLICECOMMAND_H_

class RpsliceCommand : public QueueCommand {

public: 
	RpsliceCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPSLICECOMMAND_H_
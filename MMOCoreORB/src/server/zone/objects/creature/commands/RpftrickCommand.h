/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFTRICKCOMMAND_H_
#define RPFTRICKCOMMAND_H_

class RpftrickCommand : public QueueCommand {

public: 
	RpftrickCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFTRICKCOMMAND_H_
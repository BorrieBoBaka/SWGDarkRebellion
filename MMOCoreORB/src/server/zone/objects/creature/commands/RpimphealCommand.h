/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPIMPHEALCOMMAND_H_
#define RPIMPHEALCOMMAND_H_

class RpimphealCommand : public QueueCommand {

public: 
	RpimphealCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPIMPHEALCOMMAND_H_
/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFSTHROWCOMMAND_H_
#define RPFSTHROWCOMMAND_H_

class RpfsthrowCommand : public QueueCommand {

public: 
	RpfsthrowCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFSTHROWCOMMAND_H_
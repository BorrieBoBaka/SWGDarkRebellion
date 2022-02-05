/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFJUMPCOMMAND_H_
#define RPFJUMPCOMMAND_H_

class RpfjumpCommand : public QueueCommand {

public: 
	RpfjumpCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFJUMPCOMMAND_H_
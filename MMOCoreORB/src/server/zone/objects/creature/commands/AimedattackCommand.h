/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef AIMEDATTACKCOMMAND_H_
#define AIMEDATTACKCOMMAND_H_

class AimedattackCommand : public QueueCommand {

public: 
	AimedattackCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //AIMEDATTACKCOMMAND_H_
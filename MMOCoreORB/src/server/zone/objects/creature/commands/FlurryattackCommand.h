/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef FLURRYATTACKCOMMAND_H_
#define FLURRYATTACKCOMMAND_H_

class FlurryattackCommand : public QueueCommand {

public: 
	FlurryattackCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //FLURRYATTACKCOMMAND_H_
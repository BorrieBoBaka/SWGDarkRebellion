/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFABSORBCOMMAND_H_
#define RPFABSORBCOMMAND_H_

class RpfabsorbCommand : public QueueCommand {

public: 
	RpfabsorbCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFABSORBCOMMAND_H_
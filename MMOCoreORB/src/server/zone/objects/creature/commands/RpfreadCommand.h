/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFREADCOMMAND_H_
#define RPFREADCOMMAND_H_

class RpfreadCommand : public QueueCommand {

public: 
	RpfreadCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFREADCOMMAND_H_
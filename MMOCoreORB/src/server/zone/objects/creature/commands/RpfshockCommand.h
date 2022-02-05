/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFSHOCKCOMMAND_H_
#define RPFSHOCKCOMMAND_H_

class RpfshockCommand : public QueueCommand {

public: 
	RpfshockCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFSHOCKCOMMAND_H_
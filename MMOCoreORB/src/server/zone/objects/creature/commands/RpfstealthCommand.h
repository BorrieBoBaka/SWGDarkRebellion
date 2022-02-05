/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFSTEALTHCOMMAND_H_
#define RPFSTEALTHCOMMAND_H_

class RpfstealthCommand : public QueueCommand {

public: 
	RpfstealthCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFSTEALTHCOMMAND_H_
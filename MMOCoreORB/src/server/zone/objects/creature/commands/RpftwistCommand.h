/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFTWISTCOMMAND_H_
#define RPFTWISTCOMMAND_H_

class RpftwistCommand : public QueueCommand {

public: 
	RpftwistCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFTWISTCOMMAND_H_
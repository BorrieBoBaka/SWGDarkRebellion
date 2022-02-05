/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFCRUSHCOMMAND_H_
#define RPFCRUSHCOMMAND_H_

class RpfcrushCommand : public QueueCommand {

public: 
	RpfcrushCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFCRUSHCOMMAND_H_
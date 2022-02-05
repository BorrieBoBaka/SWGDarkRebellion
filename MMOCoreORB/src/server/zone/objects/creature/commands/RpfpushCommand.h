/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFPUSHCOMMAND_H_
#define RPFPUSHCOMMAND_H_

class RpfpushCommand : public QueueCommand {

public: 
	RpfpushCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFPUSHCOMMAND_H_
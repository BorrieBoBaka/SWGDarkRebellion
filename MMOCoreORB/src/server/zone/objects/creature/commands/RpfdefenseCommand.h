/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFDEFENSECOMMAND_H_
#define RPFDEFENSECOMMAND_H_

class RpfdefenseCommand : public QueueCommand {

public: 
	RpfdefenseCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFDEFENSECOMMAND_H_
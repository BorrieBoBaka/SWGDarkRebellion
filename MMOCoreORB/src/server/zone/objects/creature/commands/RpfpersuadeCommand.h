/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFPERSUADECOMMAND_H_
#define RPFPERSUADECOMMAND_H_

class RpfpersuadeCommand : public QueueCommand {

public: 
	RpfpersuadeCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFPERSUADECOMMAND_H_
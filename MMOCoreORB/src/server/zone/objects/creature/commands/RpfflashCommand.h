/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFFLASHCOMMAND_H_
#define RPFFLASHCOMMAND_H_

class RpfflashCommand : public QueueCommand {

public: 
	RpfflashCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFFLASHCOMMAND_H_
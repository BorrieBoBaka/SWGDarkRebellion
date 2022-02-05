/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFGRIPCOMMAND_H_
#define RPFGRIPCOMMAND_H_

class RpfgripCommand : public QueueCommand {

public: 
	RpfgripCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFGRIPCOMMAND_H_
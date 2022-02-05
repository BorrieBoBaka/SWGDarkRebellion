/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFSPEEDCOMMAND_H_
#define RPFSPEEDCOMMAND_H_

class RpfspeedCommand : public QueueCommand {

public: 
	RpfspeedCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFSPEEDCOMMAND_H_
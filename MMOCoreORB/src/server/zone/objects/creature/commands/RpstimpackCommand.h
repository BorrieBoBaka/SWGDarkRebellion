/*
				Copyright <SWGEmu>
			Command written by BorrieBoBaka
		See file COPYING for copying conditions.*/

#ifndef RPSTIMPACKCOMMAND_H_
#define RPSTIMPACKCOMMAND_H_

class RpstimpackCommand : public QueueCommand {

public: 
	RpstimpackCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPSTIMPACKCOMMAND_H_
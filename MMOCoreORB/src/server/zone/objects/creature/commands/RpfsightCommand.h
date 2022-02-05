/*
				Copyright <SWGEmu>
			Command written by Borrie BoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFSIGHTCOMMAND_H_
#define RPFSIGHTCOMMAND_H_

class RpfsightCommand : public QueueCommand {

public: 
	RpfsightCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFSIGHTCOMMAND_H_
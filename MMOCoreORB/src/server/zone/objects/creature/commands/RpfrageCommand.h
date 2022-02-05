/*
				Copyright <SWGEmu>
			Command written by Borrie BoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFRAGECOMMAND_H_
#define RPFRAGECOMMAND_H_

class RpfrageCommand : public QueueCommand {

public: 
	RpfrageCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFRAGECOMMAND_H_
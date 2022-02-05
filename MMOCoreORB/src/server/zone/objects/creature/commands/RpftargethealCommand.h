/*
				Copyright <SWGEmu>
			Command written by Borrie BoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFTARGETHEALCOMMAND_H_
#define RPFTARGETHEALCOMMAND_H_

class RpftargethealCommand : public QueueCommand {

public: 
	RpftargethealCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFTARGETHEALCOMMAND_H_
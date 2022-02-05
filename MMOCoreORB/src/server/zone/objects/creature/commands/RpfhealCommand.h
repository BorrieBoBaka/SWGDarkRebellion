/*
				Copyright <SWGEmu>
			Command written by Borrie BoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFHEALCOMMAND_H_
#define RPFHEALCOMMAND_H_

class RpfhealCommand : public QueueCommand {

public: 
	RpfhealCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFHEALCOMMAND_H_
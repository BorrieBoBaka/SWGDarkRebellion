/*
				Copyright <SWGEmu>
			Command written by Borrie BoBaka
		See file COPYING for copying conditions.*/

#ifndef RPFBODYCOMMAND_H_
#define RPFBODYCOMMAND_H_

class RpfbodyCommand : public QueueCommand {

public: 
	RpfbodyCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPFBODYCOMMAND_H_
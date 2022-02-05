/*
				Copyright <SWGEmu>
			Command written by Borrie BoBaka
		See file COPYING for copying conditions.*/

#ifndef RPGFOCUSCOMMAND_H_
#define RPGFOCUSCOMMAND_H_

class RpgfocusCommand : public QueueCommand {

public: 
	RpgfocusCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
	
		return SUCCESS;
	}

};

#endif //RPGFOCUSCOMMAND_H_